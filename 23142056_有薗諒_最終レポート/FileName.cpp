#include <iostream>
#include <string>
#include <map>
#include <stdexcept>

// �ʉ݂̋��z�ƃR�[�h��ێ�����N���X
class Currency {
private:
    std::string code;
    double amount;

public:
    Currency(const std::string& currencyCode, double initialAmount)
        : code(currencyCode), amount(initialAmount) {
    }

    // �ʉ݂̃R�[�h���擾
    std::string getCode() const {
        return code;
    }

    // ���z���擾
    double getAmount() const {
        return amount;
    }
};

// �בփ��[�g���Ǘ����A�ʉݕϊ����s���N���X
class ExchangeRateManager {
private:
    // �ʉ݃R�[�h�Ɠ��{�~�ɑ΂��郌�[�g��ێ�����}�b�v
    std::map<std::string, double> rates;

public:
    // �R���X�g���N�^: �������[�g��ݒ�
    ExchangeRateManager() {
        // �������[�g (1�h��,�P���[���̓��{�~���Z)
        rates["JPY"] = 1.0;
        rates["USD"] = 147.10;// 8��7�����_�ł̃��[�g
        rates["EUR"] = 171.53;
    }

    // ���[�g���擾����֐�
    double getRate(const std::string& code) const {
        // �}�b�v������
        auto it = rates.find(code);
        if (it != rates.end()) {
            return it->second;//�ʉ݃R�[�h�ɑ΂���בփ��[�g��Ԃ�
        }
        // �ʉ݂�������Ȃ��ꍇ
        throw std::invalid_argument("�����Ȓʉ݃R�[�h�ł�: " + code);
    }


    // �ʉ݂�ʂ̒ʉ݂ɕϊ�����֐�
    Currency convert(const Currency& fromCurrency, const std::string& toCode) {
        try {
            // �ϊ����̒ʉ݂���{�~�Ɋ��Z
            double amountInJPY = fromCurrency.getAmount() * getRate(fromCurrency.getCode());

            // ���{�~����ϊ���̒ʉ݂Ɋ��Z
            double rateTo = getRate(toCode);
            double convertedAmount = amountInJPY / rateTo;

            return Currency(toCode, convertedAmount);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "�ϊ��G���[: " << e.what() << std::endl;
            return Currency("", 0.0); // �G���[���͋�̃I�u�W�F�N�g��Ԃ�
        }
    }
};

int main() {
    ExchangeRateManager rateManager;
    std::string fromCode, toCode;
    double amount;

    // ���[�U�[����
    std::cout << "�ϊ����̒ʉ݃R�[�h����͂��Ă������� (JPY, USD, EUR): ";
    std::cin >> fromCode;
    std::cout << "���z����͂��Ă�������: ";
    std::cin >> amount;
    std::cout << "�ϊ���̒ʉ݃R�[�h����͂��Ă������� (JPY, USD, EUR): ";
    std::cin >> toCode;

    // �ʉ݃I�u�W�F�N�g�̍쐬
    Currency fromCurrency(fromCode, amount);

    // �ϊ�����
    Currency convertedCurrency = rateManager.convert(fromCurrency, toCode);

    // ���ʕ\��
    if (convertedCurrency.getAmount() > 0) {
        std::cout << "-----------------------------------" << std::endl;
        std::cout << fromCurrency.getAmount() << " " << fromCurrency.getCode()
            << " �� " << convertedCurrency.getAmount() << " " << convertedCurrency.getCode()
            << " �ł��B" << std::endl;
        std::cout << "-----------------------------------" << std::endl;
    }

    return 0;
}
