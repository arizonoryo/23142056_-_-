#include <iostream>
#include <string>
#include <map>
#include <stdexcept>

// 通貨の金額とコードを保持するクラス
class Currency {
private:
    std::string code;
    double amount;

public:
    Currency(const std::string& currencyCode, double initialAmount)
        : code(currencyCode), amount(initialAmount) {
    }

    // 通貨のコードを取得
    std::string getCode() const {
        return code;
    }

    // 金額を取得
    double getAmount() const {
        return amount;
    }
};

// 為替レートを管理し、通貨変換を行うクラス
class ExchangeRateManager {
private:
    // 通貨コードと日本円に対するレートを保持するマップ
    std::map<std::string, double> rates;

public:
    // コンストラクタ: 初期レートを設定
    ExchangeRateManager() {
        // 初期レート (1ドル,１ユーロの日本円換算)
        rates["JPY"] = 1.0;
        rates["USD"] = 147.10;// 8月7日時点でのレート
        rates["EUR"] = 171.53;
    }

    // レートを取得する関数
    double getRate(const std::string& code) const {
        // マップを検索
        auto it = rates.find(code);
        if (it != rates.end()) {
            return it->second;//通貨コードに対する為替レートを返す
        }
        // 通貨が見つからない場合
        throw std::invalid_argument("無効な通貨コードです: " + code);
    }


    // 通貨を別の通貨に変換する関数
    Currency convert(const Currency& fromCurrency, const std::string& toCode) {
        try {
            // 変換元の通貨を日本円に換算
            double amountInJPY = fromCurrency.getAmount() * getRate(fromCurrency.getCode());

            // 日本円から変換先の通貨に換算
            double rateTo = getRate(toCode);
            double convertedAmount = amountInJPY / rateTo;

            return Currency(toCode, convertedAmount);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "変換エラー: " << e.what() << std::endl;
            return Currency("", 0.0); // エラー時は空のオブジェクトを返す
        }
    }
};

int main() {
    ExchangeRateManager rateManager;
    std::string fromCode, toCode;
    double amount;

    // ユーザー入力
    std::cout << "変換元の通貨コードを入力してください (JPY, USD, EUR): ";
    std::cin >> fromCode;
    std::cout << "金額を入力してください: ";
    std::cin >> amount;
    std::cout << "変換先の通貨コードを入力してください (JPY, USD, EUR): ";
    std::cin >> toCode;

    // 通貨オブジェクトの作成
    Currency fromCurrency(fromCode, amount);

    // 変換処理
    Currency convertedCurrency = rateManager.convert(fromCurrency, toCode);

    // 結果表示
    if (convertedCurrency.getAmount() > 0) {
        std::cout << "-----------------------------------" << std::endl;
        std::cout << fromCurrency.getAmount() << " " << fromCurrency.getCode()
            << " は " << convertedCurrency.getAmount() << " " << convertedCurrency.getCode()
            << " です。" << std::endl;
        std::cout << "-----------------------------------" << std::endl;
    }

    return 0;
}
