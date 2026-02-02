#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cctype>
#include <stdexcept>

// ====================== 规则配置模块（RuleConfig） ======================
/**
 * @brief 规则配置模块：管理分词规则（专有名词、独立标点），提供规则查询接口
 * @details 核心功能：存储/查询计算机专有名词、独立标点，支持从文件加载专有名词
 */
class RuleConfig 
{
private:
    // 存储计算机专有名词（如C++、Python3.10），O(1)查询效率
    std::unordered_set<std::string> computer_terms_;
    // 独立标点集合（拆分时需单独成单元）
    std::string independent_puncts_ = "!,.?;()<>{}[]:\"'\\/&>";
    // 计算机专用符号（组成专有名词的符号）
    std::string computer_symbols_ = "+-.*@#$%^&_";

public:
    /**
     * @brief 添加单个计算机专有名词
     * @param term 专有名词字符串（如"C++"）
     */
    void addComputerTerm(const std::string& term) 
    {
        computer_terms_.insert(term);
    }

    /**
     * @brief 【扩展接口1】从文件加载计算机专有名词
     * @param filePath 专有名词文件路径（每行一个名词）
     * @return 加载成功返回true，失败返回false
     */
    bool loadTermsFromFile(const std::string& filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "[Error] 无法打开专有名词文件：" << filePath << std::endl;
            return false;
        }

        std::string term;
        while (std::getline(file, term)) {
            if (!term.empty()) {
                computer_terms_.insert(term);
            }
        }
        file.close();
        std::cout << "[Info] 成功加载 " << computer_terms_.size() << " 个专有名词" << std::endl;
        return true;
    }

    /**
     * @brief 判断字符串是否为计算机专有名词
     * @param str 待判断字符串
     * @return 是专有名词返回true，否则返回false
     */
    bool isComputerTerm(const std::string& str) const 
    {
        return computer_terms_.find(str) != computer_terms_.end();
    }

    /**
     * @brief 判断字符是否为独立标点（需单独拆分）
     * @param c 待判断字符
     * @return 是独立标点返回true，否则返回false
     */
    bool isIndependentPunct(char c) const 
    {
        return independent_puncts_.find(c) != std::string::npos;
    }

    /**
     * @brief 判断字符是否为计算机专用符号（组成专有名词的符号）
     * @param c 待判断字符
     * @return 是专用符号返回true，否则返回false
     */
    bool isComputerSymbol(char c) const 
    {
        return computer_symbols_.find(c) != std::string::npos;
    }
};

// ====================== 文件读取模块（FileReader） ======================
/**
 * @brief 文件读取模块：批量读取文本文件，支持编码配置、自定义缓冲区大小
 * @details 核心功能：打开/关闭文件、批量读取内容，预留编码扩展接口
 */
class FileReader 
{
private:
    std::ifstream file_;          // 文件输入流
    std::string encoding_ = "UTF-8"; // 默认编码
    size_t default_batch_size_ = 4096; // 默认批量读取大小（4KB）

public:
    /**
     * @brief 打开指定文本文件
     * @param filePath 文件路径
     * @return 打开成功返回true，失败返回false
     */
    bool openFile(const std::string& filePath) 
    {
        // 以二进制模式打开，避免编码转换干扰
        file_.open(filePath, std::ios::binary);
        if (!file_.is_open()) {
            std::cerr << "[Error] 无法打开文件：" << filePath << std::endl;
            return false;
        }
        std::cout << "[Info] 成功打开文件：" << filePath << std::endl;
        return true;
    }

    /**
     * @brief 【扩展接口2】设置文件编码（预留接口，当前仅标识编码类型）
     * @param encoding 编码名称（如"UTF-8"、"GBK"）
     */
    void setEncoding(const std::string& encoding) 
    {
        encoding_ = encoding;
        std::cout << "[Info] 文件编码已设置为：" << encoding_ << std::endl;
    }

    /**
     * @brief 【扩展接口3】设置批量读取缓冲区大小
     * @param batchSize 缓冲区大小（字节）
     */
    void setBatchSize(size_t batchSize) 
    {
        if (batchSize < 1024) { // 最小1KB
            std::cerr << "[Warn] 缓冲区大小过小，已重置为1024字节" << std::endl;
            default_batch_size_ = 1024;
        } else {
            default_batch_size_ = batchSize;
            std::cout << "[Info] 批量读取缓冲区大小已设置为：" << default_batch_size_ << "字节" << std::endl;
        }
    }

    /**
     * @brief 批量读取文件内容
     * @param batchSize 本次读取的字节数（默认使用配置的缓冲区大小）
     * @return 读取到的字符串，空串表示读取结束或失败
     */
    std::string readBatch(size_t batchSize = 0)
    {
        if (!file_.is_open()) {
            std::cerr << "[Error] 文件未打开，无法读取" << std::endl;
            return "";
        }

        // 使用默认缓冲区大小（若未指定）
        size_t read_size = (batchSize == 0) ? default_batch_size_ : batchSize;
        std::vector<char> buffer(read_size);
        
        // 读取数据到缓冲区
        file_.read(buffer.data(), read_size);
        size_t actual_read = file_.gcount(); // 实际读取的字节数

        if (actual_read == 0) {
            return ""; // 读取结束
        }

        // 转换为字符串返回
        return std::string(buffer.data(), actual_read);
    }

    /**
     * @brief 关闭文件流
     */
    void closeFile() 
    {
        if (file_.is_open()) {
            file_.close();
            std::cout << "[Info] 文件已关闭" << std::endl;
        }
    }

    // 析构函数：确保文件流关闭
    ~FileReader() {
        closeFile();
    }
};

// ====================== 分词核心模块（TextSplitter） ======================
/**
 * @brief 分词核心模块：实现文本拆分逻辑，兼容计算机专有名词
 * @details 核心逻辑：逐字符遍历文本，拆分单词（含专有名词）和独立标点
 */
class TextSplitter 
{
private:
    RuleConfig& rule_config_; // 规则配置引用（避免拷贝）

    /**
     * @brief 辅助函数：判断字符是否为字母/数字
     * @param c 待判断字符
     * @return 是字母/数字返回true，否则返回false
     */
    bool isAlnum(char c) const 
    {
        return std::isalnum(static_cast<unsigned char>(c));
    }

public:
    /**
     * @brief 构造函数：绑定规则配置
     * @param config 规则配置对象引用
     */
    TextSplitter(RuleConfig& config) : rule_config_(config) {}

    /**
     * @brief 执行文本分词
     * @param text 待分词的文本字符串
     * @return 拆分后的结果列表（单词/标点）
     */
    std::vector<std::string> split(const std::string& text) 
    {
        std::vector<std::string> result;
        std::string current_word; // 当前单词缓冲区

        for (char c : text) 
        {
            // 1. 空白符：结束当前单词，不处理空白
            if (std::isspace(static_cast<unsigned char>(c))) 
            {
                if (!current_word.empty()) 
                {
                    // 检查是否为计算机专有名词（优先匹配）
                    if (rule_config_.isComputerTerm(current_word)) 
                    {
                        result.push_back(current_word);
                    } 
                    else 
                    {
                        result.push_back(current_word);
                    }
                    current_word.clear();
                }
                continue;
            }

            // 2. 独立标点：结束当前单词，标点单独拆分
            // ***WGA:规则2和3应该对调
            if (rule_config_.isIndependentPunct(c)) 
            {
                if (!current_word.empty()) 
                {
                    if (rule_config_.isComputerTerm(current_word)) 
                    {
                        result.push_back(current_word);
                    } 
                    else 
                    {
                        result.push_back(current_word);
                    }
                    current_word.clear();
                }
                result.push_back(std::string(1, c));
                continue;
            }

            // 3. 字母/数字/计算机符号：纳入当前单词
            // ***WGA:规则2和3应该对调
            if (isAlnum(c) || rule_config_.isComputerSymbol(c)) 
            {
                current_word += c;
                continue;
            }

            // 4. 其他字符：单独拆分
            if (!current_word.empty()) 
            {
                result.push_back(current_word);
                current_word.clear();
            }
            result.push_back(std::string(1, c));
        }  //end of for loop

        // 处理最后一个未结束的单词
        if (!current_word.empty()) 
        {
            if (rule_config_.isComputerTerm(current_word)) {
                result.push_back(current_word);
            } else {
                result.push_back(current_word);
            }
        }

        return result;
    }

    /**
     * @brief 【扩展预留】中文分词接口（当前仅占位，后续可扩展）
     * @param text 中文字本
     * @return 拆分结果列表
     */
    std::vector<std::string> splitChinese(const std::string& text) 
    {
        std::cerr << "[Warn] 中文分词功能暂未实现" << std::endl;
        return {};
    }
};

// ====================== 结果输出模块（ResultWriter） ======================
/**
 * @brief 结果输出模块：将分词结果输出到控制台/文件
 * @details 支持覆盖/追加模式，自动管理输出流资源
 */
class ResultWriter {
private:
    std::ofstream file_writer_; // 文件输出流
    bool output_to_console_ = true; // 默认输出到控制台

public:
    /**
     * @brief 初始化输出（控制台/文件）
     * @param outputPath 输出文件路径（空串表示输出到控制台）
     * @param append 是否追加模式（true=追加，false=覆盖）
     * @return 初始化成功返回true，失败返回false
     */
    bool initOutput(const std::string& outputPath = "", bool append = false) {
        if (outputPath.empty()) {
            output_to_console_ = true;
            std::cout << "[Info] 输出模式：控制台" << std::endl;
            return true;
        }

        // 配置文件输出模式
        std::ios::openmode mode = std::ios::out;
        if (append) {
            mode |= std::ios::app;
        } else {
            mode |= std::ios::trunc; // 覆盖模式
        }

        file_writer_.open(outputPath, mode);
        if (!file_writer_.is_open()) {
            std::cerr << "[Error] 无法打开输出文件：" << outputPath << std::endl;
            return false;
        }

        output_to_console_ = false;
        std::cout << "[Info] 输出模式：文件（" << (append ? "追加" : "覆盖") << "）" << std::endl;
        return true;
    }

    /**
     * @brief 输出单个拆分结果（单词/标点）
     * @param token 拆分后的单元字符串
     */
    void writeToken(const std::string& token) {
        if (output_to_console_) {
            std::cout << token << " "; // 控制台输出（空格分隔）
        } else {
            file_writer_ << token << "\n"; // 文件输出（每行一个单元）
        }
    }

    /**
     * @brief 结束输出，关闭文件流
     */
    void finishOutput() {
        if (file_writer_.is_open()) {
            file_writer_.close();
            std::cout << "[Info] 输出文件已关闭" << std::endl;
        }
        if (output_to_console_) {
            std::cout << "\n[Info] 控制台输出完成" << std::endl;
        }
    }

    // 析构函数：确保文件流关闭
    ~ResultWriter() {
        finishOutput();
    }
};

// ====================== 主函数（程序入口） ======================
int main() {
    try {
        // 1. 初始化规则配置
        RuleConfig config;
        // 手动添加部分专有名词
        config.addComputerTerm("C++");
        config.addComputerTerm("Python3.10");
        config.addComputerTerm("Java8-SE");
        // 【扩展接口1】从文件加载专有名词（需提前创建terms.txt文件）
        if (!config.loadTermsFromFile("terms.txt")) {
            std::cerr << "[Warn] 未加载外部专有名词文件，使用内置规则" << std::endl;
        }

        // 2. 初始化文件读取
        FileReader reader;
        // 【扩展接口2】设置文件编码
        reader.setEncoding("UTF-8");
        // 【扩展接口3】设置批量读取缓冲区大小（8KB）
        reader.setBatchSize(8192);
        // 打开输入文件（替换为你的文本文件路径）
        if (!reader.openFile("input.txt")) {
            return 1;
        }

        // 3. 初始化结果输出（输出到文件output.txt，覆盖模式）
        ResultWriter writer;
        if (!writer.initOutput("output.txt", false)) {
            return 1;
        }

        // 4. 初始化分词器
        TextSplitter splitter(config);

        // 5. 批量读取+分词+输出
        std::cout << "[Info] 开始分词处理..." << std::endl;
        std::string batchText;
        while (!(batchText = reader.readBatch()).empty()) {
            std::vector<std::string> tokens = splitter.split(batchText);
            for (const auto& token : tokens) {
                writer.writeToken(token);
            }
        }

        // 6. 资源释放（析构函数会自动处理，此处显式调用更清晰）
        reader.closeFile();
        writer.finishOutput();

        std::cout << "[Info] 分词处理完成！" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[Error] 程序异常：" << e.what() << std::endl;
        return 1;
    }

    return 0;
}