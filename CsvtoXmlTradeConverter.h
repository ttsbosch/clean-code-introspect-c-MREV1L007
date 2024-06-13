#ifndef CSV_TO_XML_TRADE_CONVERTER_H_
#define CSV_TO_XML_TRADE_CONVERTER_H_

#include "TradeRecord.h"
#include "StringHelpers.h"

#define MAX_LINE_LENGTH 1024
#define MAX_TRADES 1024
#define LOT_SIZE 100

// Function prototypes
void csvtoxmlconverter(const char* line, TradeRecord* trade);
void writeTradeToXML(FILE* outFile, const TradeRecord* trade);
void process(FILE* stream);


#endif /*end of CSV_TO_XML_TRADE_CONVERTER_H_*/
