#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "CsvtoXmlTradeConverter.h"

void csvtoxmlconverter(const char* line, TradeRecord* trade) {
        char** fields = SplitString(line, ',');
    if (strlen(fields[0]) != 6) {
        fprintf(stderr, "WARN: Malformed trade currencies: '%s'\n", fields[0]);
        return;
    }

    int amount;
    if (!intGetFromString(fields[1], &amount)) {
        fprintf(stderr, "WARN: Invalid trade amount: '%s'\n", fields[1]);
        return;
    }

    double price;
    if (!toDouble(fields[2], &price)) {
        fprintf(stderr, "WARN: Invalid trade price: '%s'\n", fields[2]);
        return;
    }

    strncpy(trade->SrcCurrency, fields[0], 3);
    trade->SrcCurrency[3] = '\0';
    strncpy(trade->DestCurrency, fields[0] + 3, 3);
    trade->DestCurrency[3] = '\0';
    trade->Lots = amount / (float)LOT_SIZE;
    trade->Price = price;

    for (int i = 0; fields[i] != NULL; i++) {
        free(fields[i]);
    }
    free(fields);
}

// Writes a single TradeRecord to an XML file
void writeTradeToXML(FILE* outFile, const TradeRecord* trade) {
    fprintf(outFile, "\t<TradeRecord>\n");
    fprintf(outFile, "\t\t<SourceCurrency>%s</SourceCurrency>\n", trade->SrcCurrency);
    fprintf(outFile, "\t\t<DestinationCurrency>%s</DestinationCurrency>\n", trade->DestCurrency);
    fprintf(outFile, "\t\t<Lots>%.2f</Lots>\n", trade->Lots);
    fprintf(outFile, "\t\t<Price>%.2f</Price>\n", trade->Price);
    fprintf(outFile, "\t</TradeRecordModified>\n");
}

// Processes the input stream and extracts trade records
void Extracttraderecord(FILE* stream) {
    char line[MAX_LINE_LENGTH];
    TradeRecord trades[MAX_TRADES];
    int tradeCount = 0;

    while (fgets(line, sizeof(line), stream) && tradeCount < MAX_TRADES) {
        csvtoxmlconverter(line, &trades[tradeCount]);
        tradeCount++;
    }

    FILE* outFile = fopen("output.xml", "w");
    if (!outFile) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fprintf(outFile, "<TradeRecords>\n");
    for (int tradeIndex = 0; tradeIndex < tradeCount; tradeIndex++) {
        writeTradeToXML(outFile, &trades[tradeIndex]);
    }
    fprintf(outFile, "</TradeRecords>\n");
    fclose(outFile);

    printf("INFO: %d trades processed\n", tradeCount);
}

int main() {
    FILE* inputFile = fopen("trades.txt", "r");
    if (!inputFile) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    Extracttraderecord(inputFile);
    fclose(inputFile);

    return EXIT_SUCCESS;
}
