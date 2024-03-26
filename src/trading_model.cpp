// Copyright 2024, Andrew Drogalis
// GNU License

#include "trading_model.h"

#include <unordered_map>
#include <vector>
#include <string>

namespace fxordermgmt {
    
TradingModel::TradingModel() { }

TradingModel::~TradingModel() { }

TradingModel::TradingModel(std::unordered_map<std::string, std::vector<float>> historical_data){

    std::vector<float> open_data = historical_data["Open"];
    std::vector<float> high_data = historical_data["High"];
    std::vector<float> low_data = historical_data["Low"];
    std::vector<float> close_data = historical_data["Close"];
    std::vector<float> datetime_data = historical_data["Datetime"];

}

void TradingModel::receive_latest_market_data(std::unordered_map<std::string, std::vector<float>> historical_data) {
    // User Defined Trading Model
}

int TradingModel::send_trading_signal(){

    float signal = ((double) rand() / (RAND_MAX));

    signal = (signal > 0.5) ? 1 : -1;

    return signal;
}

} // namespace fxordermgmt

