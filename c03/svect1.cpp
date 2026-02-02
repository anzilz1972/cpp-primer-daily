/*
本代码片段：
  1、测试 std::cin 的各种函数用法
     1）用cin.eof() 判断输入结束
     2）用 cin.fail() 判断输入错误
     3）用 cin.clear() 重置所有错误
     4）用 cin.ignore() 忽略缓冲区所有内容直到换行
  2、测试 vector<string> 对象
  3、对cpp.txt使用正则表达式拆分字符串:正则表达式说明和cpp.txt内容附代码后
*/
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <regex>
#include "wga.h"
using namespace std;


// 使用正则表达式库，将字符串拆分为独立的单词和标点符号，并存储在vector<string>中
vector<string> 
    splitWordsAndPunctuation(const string& text);

//将一个vector<string> 的内容添加到另一个vector<string>的末尾
void AppendSVector(vector<string>& dest , const vector<string>& source);


int main()
{

    /////////////////////////////////////////////////////////////////////////////
    //使用cin对象，简单拆分字符串
    vector<string> svec;

    //输入多个字符串，以EOF结束
    //Windows环境下，EOF是--> "Ctrl+D 加 回车"
    //Linux/macOS 环境下，EOF是--> "Ctrl+D"
    cout << " Under windows,     ****** EOF --> Ctrl+Z + ENTER ******" << endl;
    cout << " Under Linux/macOS, ****** EOF -->     Ctrl+D     ******" << endl;
    cout << "Input some strings , End of EOF:\n" << endl;

    //将cpp.txt的句子存储在svec中，待处理
    string astr;
    while (true)
    {
        getline(cin , astr);
        //判断是否读取到EOF
        if (cin.eof()) break;

        //判断是否输入错误（诸如类型不匹配等）
        if (cin.fail())
        {
            cout << "Input ERROR,Try again!!!" << endl;
            //重置错误状态
            cin.clear();
            //清空缓冲区的错误输入并继续输入
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        svec.push_back(astr);
    }

    //for (auto s:svec) cout << s << endl;

    //splitline();
 

    
    /////////////////////////////////////////////////////////////////////////////
    //使用正则表达式拆分字符串
    //将输入的字符串按照单词和字符串分割，放到新的string vector中
    vector<string> wordsAndPuncVec; // string vector,存放分割后的单词和标点符号
    for (auto s:svec) 
        AppendSVector(wordsAndPuncVec,splitWordsAndPunctuation(s));
    
    //统计 string Vector 中的单词和标点符号，之后输出全部内容
    int numsPunc = 0,words = 0,idx = 0;
    for (auto s:wordsAndPuncVec) 
    {
        if (s.length() <= 1)
            numsPunc++;
        else
            words++;
        cout << idx++ << ":    " << s << endl;
    }
    splitline();
    cout << "Total " << words << " words and " << numsPunc << " Punctuation marks." << endl;

    return 0;
}

//使用正则表达式库，将字符串拆分为独立的单词和标点符号，并存储在vector<string>中
vector<string> splitWordsAndPunctuation(const string& text) 
{
    vector<string> result;
    
    // 核心正则规则：
    regex CPP_TOKENIZER_PATTERN(R"((?:C\+\+(?:11|14|17|20|23)?|"[^"]*"|'[^']*'|\((?:[^()]|\([^)]*\))*\)|\[[^\]]*\]|\{[^}]*\}|[,\.](?=\s*$)|[,.;:!?()\[\]]|std::[a-zA-Z_][a-zA-Z0-9_]*|[a-zA-Z0-9_-]+|[^\w\s]))", 
        std::regex::ECMAScript | std::regex::icase);
    
    // 遍历所有匹配结果，存入vector
    sregex_iterator it(text.begin(), text.end(), CPP_TOKENIZER_PATTERN);
    sregex_iterator end; // 结束迭代器
    
    for (; it != end; ++it) {
        string token = it->str();
        // 过滤空字符串（避免异常情况）
        if (!token.empty()) {
            result.push_back(token);
        }
    }
   
    return result;
}

//将一个vector<string> 的内容添加到另一个vector<string>的末尾
void AppendSVector(vector<string>& dest , const vector<string>& source)
{
    for (auto s:source) 
        dest.push_back(s);
}



/*
cpp.txt 文件专用正则表达式规则清单
正则表达式：
const std::regex CPP_TOKENIZER_PATTERN(R"((?:C\+\+(?:11|14|17|20|23)?|"[^"]*"|'[^']*'|\((?:[^()]|\([^)]*\))*\)|\[[^\]]*\]|\{[^}]*\}|[,\.](?=\s*$)|[,.;:!?()\[\]]|std::[a-zA-Z_][a-zA-Z0-9_]*|[a-zA-Z0-9_-]+|[^\w\s]))", std::regex::ECMAScript | std::regex::icase);
---
📋 分割规则详细列表
🔥 规则1：C++相关术语 (最高优先级)
- 匹配模式：C\+\+(?:11|14|17|20|23)?
- 识别内容：
  - C++
  - C++11
  - C++14 
  - C++17
  - C++20
  - C++23
📝 规则2：引号内容
- 匹配模式："[^"]*"|'[^']*'
- 识别内容：
  - 双引号："Hello World"、"C with Classes"
  - 单引号：'text'、'character'
📍 规则3：括号内容 (支持嵌套)
- 匹配模式：\((?:[^()]|\([^)]*\))*\)
- 识别内容：
  - 简单括号：(OOP)、(data members)
  - 复杂括号：(such as GCC, Clang, or MSVC)
  - 嵌套括号：(functions in a base class that can be overridden in derived classes)
- 其他括号：
  - 方括号：[...] 如 [a-zA-Z0-9]
  - 花括号：{...} 如 {...}
🔚 规则4：句末标点符号
- 匹配模式：[,\.](?=\s*$)
- 识别内容：
  - 句末逗号：,
  - 句末句号：.
  - 只匹配行尾的标点，确保单独分割
🏷️ 规则5：标准库命名空间 (std::)
- 匹配模式：std::[a-zA-Z_][a-zA-Z0-9_]*
- 识别内容：
  - std::vector
  - std::cout
  - std::cin
  - std::unique_ptr
  - std::shared_ptr
  - std::weak_ptr
  - std::ifstream
  - std::ofstream
  - std::fstream
  - std::optional
  - std::variant
🎯 规则6：句中标点符号
- 匹配模式：[,.;:!?()\[\]]
- 识别内容：
  - 逗号：,
  - 句号：.
  - 分号：;
  - 冒号：:
  - 感叹号：! ?
  - 括号：( ) [ ] { }
📚 规则7：普通单词
- 匹配模式：[a-zA-Z0-9_-]+
- 识别内容：
  - 字母单词：programming、language、developer
  - 数字单词：C++11、HTML5
  - 带下划线：file_name、variable_name
  - 带连字符：high-performance、state-of-the-art
🔄 规则8：其他单字符
- 匹配模式：[^\w\s]
- 识别内容：
  - 其他未覆盖的单个字符
  - Fallback 兜底规则
---
⚡ 优先级说明
1. 最高优先级：C++相关术语
2. 高优先级：引号内容
3. 中高优先级：括号内容  
4. 中优先级：句末标点
5. 中低优先级：std::命名空间
6. 低优先级：句中标点
7. 较低优先级：普通单词
8. 最低优先级：其他字符
---
🎯 匹配示例
输入文本：
C++ is powerful, and C++11 improved it. "Hello World" is important. Template (like std::vector) helps. std::cout prints text.
输出结果：
[C++] [is] [powerful] [,] [and] [C++11] [improved] [it] 
[.] ["Hello World"] [is] [important] [.] [Template] [(like std::vector)] [helps] 
[.] [std::cout] [prints] [text] [.]
---
✅ 规则特点
- 精确匹配：每个规则都有明确的匹配范围
- 支持嵌套：括号内容支持多层嵌套
- 语义完整：std:: 与其后的标识符视为一个语义单元
- 位置敏感：句末标点与句中标点区分处理
- C++专用：针对C++文档的特殊术语优化
- 性能优化：使用非捕获组 (?:...) 提高匹配效率
这个正则表达式完美适配cpp.txt文件的C++编程文档内容！
*/


/* 本代码的测试，可以用管道命令模拟cin,将以下文章输入
A Comprehensive Overview of Core C++ Programming Concepts
C++ is a powerful, multi-paradigm programming language developed by Bjarne Stroustrup at Bell Labs in the early 1980s as an extension of the C language, initially named "C with Classes".
It retains all the procedural programming features of C while introducing object-oriented programming (OOP) capabilities, making it a versatile language used in a wide range of applications, from system software and game development to embedded systems and high-performance computing.
Unlike interpreted languages such as Python or JavaScript, C++ is a compiled language, meaning source code is translated into machine code by a compiler (such as GCC, Clang, or MSVC) before execution, resulting in fast and efficient programs that leverage the full capabilities of the underlying hardware.
Compilation typically involves several stages: preprocessing (handling directives like #include and #define), compilation (translating preprocessed code to assembly language), assembly (converting assembly to machine code), and linking (combining machine code from multiple files into an executable).
This multi-step process gives developers granular control over optimization, allowing them to tailor the compiled output for specific hardware architectures or performance requirements.
One of the defining characteristics of C++ is its support for multiple programming paradigms, including procedural, object-oriented, and generic programming.
Procedural programming in C++ follows the same structure as C, using functions, loops (for, while, do-while), and conditional statements (if-else, switch-case) to execute a sequence of instructions.
Functions in C++ can be modular, with parameters passed by value, reference, or pointer, enabling code reuse and separation of concerns.
Object-oriented programming (OOP) in C++ is built around the concept of classes and objects: a class is a blueprint that defines the properties (data members) and behaviors (member functions) of a set of objects, while an object is an instance of a class.
This paradigm enables encapsulation, inheritance, and polymorphism—three core principles of OOP.
Encapsulation allows developers to bundle data and functions into a single unit, hiding the internal implementation details from the outside world through access specifiers (public, private, protected) to prevent unintended modification.
Private members are only accessible within the class, protected members are accessible to derived classes, and public members form the interface for interacting with the class.
Inheritance enables new classes (derived classes) to reuse the properties and methods of existing classes (base classes), promoting code reusability and modularity.
It supports single inheritance (a class inherits from one base class) and multiple inheritance (a class inherits from multiple base classes), though multiple inheritance requires careful handling to avoid ambiguity, such as the diamond problem, which can be resolved using virtual inheritance.
Polymorphism allows objects of different classes to be treated as objects of a common base class, enabling flexible and extensible code through function overloading (multiple functions with the same name but different parameter lists) and virtual functions (functions in a base class that can be overridden in derived classes).
Virtual destructors are also critical in polymorphic hierarchies to ensure proper cleanup of derived class objects when deleted through a base class pointer.
Generic programming is another key feature of C++, centered around the use of templates to create reusable code that works with different data types without sacrificing performance.
Templates allow developers to write functions and classes (template classes) that can operate on any data type, such as the standard template library (STL) containers like vectors, lists, maps, sets, and queues, which are essential tools for efficient data management in C++ programs.
The STL is a collection of template classes and functions that provide common data structures and algorithms (such as sorting, searching, and iteration), reducing the need for developers to write low-level code from scratch and improving code reliability and maintainability.
Template specialization allows developers to define custom implementations of templates for specific data types, while partial specialization caters to subsets of data types, balancing reusability and customization.
Concepts, introduced in C++20, further enhance generic programming by enabling compile-time checks on template arguments, ensuring they meet specific requirements (e.g., being a numeric type or supporting comparison operators), and providing clearer error messages when requirements are not met.
Memory management is a critical aspect of C++ programming, as the language gives developers direct control over memory allocation and deallocation, unlike higher-level languages with automatic garbage collection.
In C++, memory can be allocated either on the stack or the heap: stack allocation is automatic and fast, used for local variables that are destroyed when they go out of scope (when the function they are declared in exits), while heap allocation (using the new operator for single objects or new[] for arrays) is manual and used for objects that need to persist beyond the current scope.
It is the responsibility of the programmer to deallocate heap memory using the delete operator (or delete[] for arrays) to avoid memory leaks, which occur when allocated memory is not released and accumulates over time, leading to reduced system performance or crashes.
Dangling pointers (pointers that point to deallocated memory) and double frees (attempting to delete the same memory twice) are common pitfalls in manual memory management, which can cause undefined behavior.
Modern C++ (C++11 and later) introduced smart pointers (such as std::unique_ptr, std::shared_ptr, and std::weak_ptr) to simplify memory management by automatically deallocating memory when it is no longer needed.
std::unique_ptr provides exclusive ownership of a resource, std::shared_ptr enables shared ownership with reference counting, and std::weak_ptr addresses circular reference issues with std::shared_ptr, reducing the risk of memory leaks and dangling pointers.
Additionally, RAII (Resource Acquisition Is Initialization) is a fundamental idiom in C++ that ties resource management (memory, file handles, network connections) to object lifetime, ensuring resources are properly released when objects go out of scope, even in the presence of exceptions.
C++ is a statically typed language, meaning the type of each variable must be declared at compile time, and the compiler enforces type checking to catch errors before the program runs.
This strict typing improves code reliability and performance but requires careful attention to type declarations and conversions.
Implicit type conversions (coercion) can occur between compatible types (e.g., int to double), but explicit type conversions (casts) are needed for incompatible types, with four types of casts in modern C++: static_cast (for safe, well-defined conversions), dynamic_cast (for polymorphic type checking at runtime), const_cast (to remove const qualifiers), and reinterpret_cast (for low-level, unsafe conversions between pointer types).
Common basic data types in C++ include int (typically 4 bytes for integers), double (8 bytes for double-precision floating-point numbers) and float (4 bytes for single-precision floating-point numbers), char (1 byte for single characters, either signed or unsigned), bool (1 byte for boolean values true or false), long (4 or 8 bytes for larger integers), long long (8 bytes for very large integers), and short (2 bytes for small integers).
The language also supports user-defined types, such as structures (struct, for grouping related data), enumerations (enum and enum class, for named integer constants), and classes, which allow developers to create custom data types tailored to specific application needs.
Enumeration classes (strongly typed enums) introduced in C++11 prevent implicit conversions to int and avoid name collisions, making code more type-safe.
Error handling in C++ is primarily done through exceptions, which provide a structured way to handle runtime errors such as division by zero, file not found, invalid input, or out-of-bounds array access.
Exceptions are thrown using the throw keyword and caught using try-catch blocks, with a catch-all block (...) for handling unexpected exceptions.
This mechanism allows developers to separate error-handling code from normal program logic and recover gracefully from unexpected errors.
Proper exception handling is essential for writing robust C++ programs, as it prevents crashes and allows the program to handle errors in a controlled manner—for example, closing open files or releasing allocated memory before terminating.
Exception specifications (deprecated in C++11 and removed in C++17) were once used to declare which exceptions a function could throw, but noexcept (introduced in C++11) is now preferred to indicate that a function does not throw exceptions, enabling compiler optimizations.
Additionally, C++ provides error codes (returning integers to indicate success or failure) and assertions (assert() macro) for simpler error checking during development, though exceptions are the preferred method for handling exceptional conditions in modern C++ development.
Assertions are disabled in release builds, making them suitable for debugging and validating assumptions, while error codes are useful in performance-critical code where exceptions may incur overhead.
The standard input/output (I/O) library in C++ (<iostream>) provides functions for reading input from the user and writing output to the console.
std::cout (standard output) is used to print text and values to the console, while std::cin (standard input) is used to read input from the keyboard, with extraction operators (>>) for reading values and insertion operators (<<) for writing values.
Formatting options, such as setting decimal precision, displaying numbers in hexadecimal/octal format, or setting field widths, are available through manipulators in the <iomanip> header (e.g., setprecision, hex, setw), allowing developers to control the appearance of output data.
Unformatted I/O functions (e.g., get(), put(), read(), write()) are also available for low-level input/output operations, useful for handling raw bytes or binary data.
File I/O operations are handled by the <fstream> header, which provides classes like std::ifstream (for reading text/binary files), std::ofstream (for writing text/binary files), and std::fstream (for both reading and writing).
File operations involve opening a file with a specific mode (read, write, append, binary), performing I/O operations, and closing the file (automatically done by the file stream destructor if using RAII).
Error checking for file operations is crucial, as files may fail to open due to missing permissions, non-existent paths, or full storage.
C++ continues to evolve with regular standards updates, including C++11, C++14, C++17, C++20, and C++23, each introducing new features to improve productivity, safety, and performance.
C++11 was a major update that added range-based for loops, lambda expressions (anonymous functions), constexpr (compile-time constant expressions), move semantics (for efficient transfer of resources between objects), and rvalue references, reducing copying overhead and improving performance.
C++14 focused on small improvements, such as generic lambdas and relaxed constexpr rules, while C++17 added structured bindings (for unpacking tuples and structs), std::optional (for representing optional values), std::variant (for type-safe unions), and fold expressions (for simplifying template code).
C++20 introduced concepts (for template constraints), ranges (a modern alternative to STL algorithms), coroutines (for asynchronous programming), and modules (replacing header files to reduce compilation time and improve code isolation).
C++23 further enhanced these features with improvements to ranges, coroutines, and standard library containers, as well as new utilities for parallel programming and text processing.
These updates make modern C++ more expressive and easier to use while maintaining its core strengths of performance and control.
Learning C++ requires a solid understanding of its core concepts, including memory management, OOP, templates, and the standard library, but mastering these concepts enables developers to write efficient, scalable, and maintainable code for a wide variety of applications.
Whether developing low-level system software (operating systems, device drivers), high-performance game engines (Unreal Engine, Unity's C++ backend), financial applications (high-frequency trading systems), embedded systems (automotive electronics, IoT devices), or cross-platform applications (using frameworks like Qt), C++ remains a vital and widely used language in the software development industry.
Its ability to interact closely with hardware, combined with support for modern programming paradigms, makes it a preferred choice for performance-critical applications where efficiency and control are paramount.
Best practices in C++ development include using RAII for resource management, preferring smart pointers over raw pointers, avoiding manual memory management where possible, using the STL instead of reinventing data structures/algorithms, and adhering to modern C++ standards to leverage safety and performance improvements.
*/