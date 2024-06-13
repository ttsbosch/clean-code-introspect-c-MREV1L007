#ifndef TRADE_RECORD_H_
#define TRADE_RECORD_H_

typedef struct {
    char SrcCurrency[256];
    char DestCurrency[256];
    float Lots;
    double Price;
} TradeRecord;

#endif /*End of TRADE_RECORD_H */
