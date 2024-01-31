
# FX Order Management

## Table of Contents

* [Getting Started](#Getting-Started)
    * [Downloading Dependencies](#Downloading-Dependencies)
* [Instructions](#Instructions)
    * [Storing User Credentials](#Storing-User-Credentials)
    * [Updating Order Parameters](#Updating-Order-Parameters)
    * [Setting Password in Keyring](#Setting-Password-in-Keyring)
    * [Updating Trading Model](#Updating-Trading-Model)
    * [Switch to Live Trading](#Switch-to-Live-Trading)
* [Building Executable](#Building-Executable)
* [Dependencies](#Dependencies)
* [License](#License)
* [Contributing](#Contribution)

## Getting Started

This repository is dependent upon the API from Gain Capital's Forex.com. To make an account visit their website [Forex.com](https://www.forex.com). Once an account is made you will need to send them an email and request an API key.

### Downloading Dependencies

Please see a link to required dependencies [below](#Dependencies). If you are in Linux, Boost & OpenSSL & libsecret can be installed with the following commands below. Since this repository has been built and tested on a Linux system, please open up an issue if there are any conflicts with Windows or Mac OS.

```
    Fedora:
        dnf install boost-devel openssl-devel libsecret-devel
    Debian:
        apt-get install libboost-all-dev libssl-dev libsecret-1-dev
    Arch: 
        pacman -Ss boost
        pacman -S --needed openssl
        pacman -Sy libsecret
```

## Instructions

### Storing User Credentials

```c
    #ifndef CREDENTIALS_H
    #define CREDENTIALS_H

    #include <string>
    #include <vector>

    using namespace std;

    string account_username = "BLANK";

    string paper_account_username = "BLANK";

    string forex_api_key = "BLANK";

    // Store Passwords in Keyring.

    #endif
```

### Updating Order Parameters

```c
    #ifndef TRADING_PARAMS_H
    #define TRADING_PARAMS_H

    #include <string>
    #include <vector>

    using namespace std;

    vector<string> fx_symbols_to_trade = {"USD/JPY", "EUR/USD", "USD/CHF", "USD/CAD"};

    int order_position_size = 2'000; // Lot Size

    int num_data_points = 10'000;

    string update_interval = "MINUTE"; // MINUTE or HOUR

    int update_span = 5; // Span of Interval e.g. 5 Minutes

    #endif
```

### Setting Password in Keyring

User will be prompted the first time they use the application. The password will be stored securely in the keyring and automatically loaded for the next use.

```c
   if (account_type == "PAPER") {
        error = keychain::Error{};
        password = keychain::getPassword(package_test, service_id_test, paper_account_username, error);
        
        if (error.type == keychain::ErrorType::NotFound) {
            std::cout << "Test Account password not found. Please input password: ";
            cin >> test_account_password;

            // Test Password Setup
            keychain::setPassword(package_test, service_id_test, paper_account_username, test_account_password, error);
            if (error) {
                std::cerr << "Test Account " << error.message << std::endl;
                std::terminate();
            }
        } else if (error) {
            std::cerr << error.message << std::endl;
            std::terminate();
        }
    }
```

### Updating Trading Model

Please don't run in a live trading environment with the placeholder trading model provided. 

```c
#include <trading_model.h>
#include <map>
#include <vector>
#include <string>

using namespace std;

TradingModel::TradingModel() { }

TradingModel::TradingModel(map<string, vector<float>> historical_data){

    vector<float> open_data = historical_data["Open"];
    vector<float> high_data = historical_data["High"];
    vector<float> low_data = historical_data["Low"];
    vector<float> close_data = historical_data["Close"];
    vector<float> datetime_data = historical_data["Datetime"];

}

void TradingModel::receive_latest_market_data(map<string, vector<float>> historical_data) {

}

int TradingModel::send_trading_signal(){

    float signal = ((double) rand() / (RAND_MAX));

    signal = (signal > 0.5) ? 1 : -1;

    return signal;
}
```

### Switch to Live Trading

The default is paper trading, switch to live account and set place trades to true.

```c
int main() {
    // Set Account Type
    string ACCOUNT = "PAPER"; 
    bool PLACE_TRADES = false; 
```

# Building Executable

```
    $ mkdir build
    $ cmake -S . -B build
    $ cmake --build build --target FX_Order_Management
```

# Dependencies

- [Boost](https://www.boost.org/) - *Must be installed by user*
- [Libsecret](https://wiki.gnome.org/Projects/Libsecret) - *For Linux, Must be installed by user*
- [OpenSSL](https://www.openssl.org/) - *Must be installed by user*
- [CPR](https://github.com/libcpr/cpr) - Included in CMake Fetch Content
- [JSON](https://github.com/nlohmann/json) - .hpp file included in repository
- [Keychain](https://github.com/hrantzsch/keychain) - Library included in repository

## License

This software is distributed under the GNU license. Please read [LICENSE](https://github.com/andrew-drogalis/FX-Order-Management/blob/main/LICENSE) for information on the software availability and distribution.

## Contribution

Please open an issue of if you have any questions, suggestions, or feedback.

Please submit bug reports, suggestions, and pull requests to the [GitHub issue tracker](https://github.com/andrew-drogalis/FX-Order-Management/issues).