# Github 项目地址

[github]()

# 具体分工

- 佘岳昕 : 爬虫设计、命令行解析实现
- 王源 : 主要框架设计、 内容过滤实现、 权重功能实现、 输出个数功能实现、 词组功能实现


# PSP表格

PSP2.1 | 	Personal Software Process Stages |	预估耗时（分钟） |实际耗时（分钟）  
---|---|---|---
 Planning | 	计划 | 15 |8
· Estimate | 	· 估计这个任务需要多少时间 | 15 | 8
Development | 开发  | 960| 1080
· Analysis | 	· 需求分析 (包括学习新技术)  | 30| 30
· Design Spec | 	· 生成设计文档  | 40|  20
· Design Review | 	· 设计复审| 20| 20
· Coding Standard | 	· 代码规范 (为目前的开发制定合适的规范)  | 15 | 15
·  Design | 	· 具体设计  | 600| 750
· Coding| 	· 具体编码  | 210| 300
· Code Review | 	· 代码复审  |10 | 10
· Test | 	· 测试（自我测试，修改代码，提交修改）  | 120| 150
Reporting| 	报告  | 120| 
· Test Repor | 	· 测试报告  | 115| 10
· Size Measurement | 	· 计算工作量  | 20| 15
· Postmortem & Process Improvement Plan | 	· 事后总结, 并提出过程改进计划  |90 | 60
    |       | 	合计  | | 


# 解题思路描述 && 设计实现说明

拿到题目后，我们首先基于各自的框架思考了一下如何实现，并进行对比。从而得出第一张初步的流程图。

经过了n次迭代以及代码完成后的细节修补↓, 终于得到了最后的类图，见后面的部分。



## 爬虫使用说明

## 代码组织与内部实现设计

### `Status`类
    
存储各个设置、运行结果、常量

### `ArgParse`类

解析用户的输入参数并验证其合法性，根据解析结果设置`Status`类

### `FileContentFilter`类

过滤输入文件中"Title: "等无用部分，分割"Title"串和"Abstract"串，将串送给`LexemeParser`类

[]

### `LexemeParser`类

- 分离字符串为字母串和分隔符串（对换行符特殊处理）,送给`LexemeProcesser`类
- 统计字符总数、行数

[]

### `LexemeProcesser`类

- `WordProcesser`类和 `PhraseProcesser`类的父类
- 对字母串和分隔符串组成的词素进行合法性判断， 并存储


# 附加题设计与展示

设计的创意独到之处
实现思路
实现成果展示



# 关键代码解释

# 代码说明

    class ScanProcesser{

    private:
        int charNum;
        int wordNum;
        int wordNumTotal;
        int lineNum;
        int inWord;// IN = 1, OUT = 0 标志扫描指针在一个疑似单词串中
        int newLine;// OLD = 1, NEW = 0
                    // 标志此行有无非空白符，即是否为新行
        stringstream* ss; //存储当前找到的可疑单词序列
        const int SPACE = ' ';
        const int LINESYM = '\n';
        const int TAB = '\t';
        const int LINKWORDSYM = '-';
    };

    // 处理单个字符并更新数据
    int ScanProcesser::processChar(char c){
        
        // 存储当前找到的单词
        string nowWord;

        if (c == EOF) {
            if (newLine == OLD)

                // 当文件最后一行有数据时，行数增加1
                lineNum++;
        }
        else {

            // 中文字符不对字符数影响
            if (isascii(c))
                charNum++;
            else {
                c = TAB;
            }
        }

        //遇到换行符时刷新空行标志
        if (c == LINESYM) {
            if (newLine == OLD) {
                newLine = NEW;
                lineNum++;
            }
        }
        else {
            if (newLine == NEW) {
                if (!(c == SPACE || c == TAB))
                    newLine = OLD;
            }
        }
        
        // 遇到分隔符
        if (!(isalnum(c))){
            
            // 在可疑单词序列内，则判断单词合法性，将合法单词存入map
            if (inWord == IN) {
                *ss >> nowWord;
                if (checkWordValid(nowWord)) {
                    map<string, int>::iterator iter;

                    iter = strMap->find(nowWord);

                    if (iter != strMap->end()) {
                        wordNumTotal++;
                        int count = (iter->second) + 1;
                        strMap->erase(iter);
                        strMap->insert(pair<string, int>(nowWord, count));
                    }
                    else {
                        wordNum++;
                        wordNumTotal++;
                        strMap->insert(pair<string, int>(nowWord, 1));
                    }
                }
                inWord = OUT;
                delete ss;
                ss = new stringstream();//刷新ss
            }
            else;
        }
        else if (isalnum(c)){
            if (isalpha(c))
                c = tolower(c);
            if (inWord == IN);
            else{
                // 若不在可疑单词序列内，置标志位为IN
                // 视为进入可疑单词序列
                inWord = IN;
            }
            *ss << c;
        }
        else;
        return 0;
    }




# 性能分析与改进


这次工程中，对程序的改进大规模出现在类图、流程图的制作过程中，小规模出现在程序实现时。

在性能分析之后，发现占比最大的依然分别是std::string和std::map。



# 单元测试

测试采用Microsoft本机测试框架
测试数据先测试基本情况的正确性，之后测试更难一点的情况的正确性

    // path: /test/UnitTest_LexemeParser/unittest1.cpp
    namespace UnitTest_LexemeParser
    {        
        TEST_CLASS(UnitTest1)
        {
        public:


            TEST_METHOD(TestMethod1)
            {
                Status* status = new Status();
                WordProcesser* lexProcesser = new WordProcesser(status);
                LexemeParser* lexer = new LexemeParser(status, lexProcesser);

                lexer->processStr("We present a new AI task -- Embodied Question Answering (E"
                    "mbodiedQA) -- where an agent is spawned at a random location in a 3D envi"
                    "ronment and asked a question", Status::TITLE_CONTENT);
                lexer->sendToStatus();
                lexProcesser->sendToStatus();

                Assert::AreEqual<int>(159, status->charNum);
                Assert::AreEqual<int>(1, status->lineNum);

            }

            TEST_METHOD(TestMethod2)
            {
                Status* status = new Status();
                status->setPharse(3);

                PhraseProcesser* lexProcesser = new PhraseProcesser(status);
                LexemeParser* lexer = new LexemeParser(status, lexProcesser);

                lexer->processStr("adbda \n afasdf asdfasdf aqsf", Status::TITLE_CONTENT);
                lexer->sendToStatus();
                lexProcesser->sendToStatus();

                Assert::AreEqual<int>(28, status->charNum);
                Assert::AreEqual<int>(2, status->lineNum);
                Assert::AreEqual<int>(1, ((status->storeMap).strMap->size()));
            }


        };
    }

# Github的代码签入记录

# 遇到的代码模块异常或结对困难及解决方法

# 评价你的队友

## 值得学习的地方



## 需要改进的地方


# 学习进度条


| | | | | | |
|---|---|---|---|---|---|
|第N周|新增代码（行)|累计代码（行）|本周学习耗时(小时)|累计学习耗时（小时）|重要成长|
|1 |312|312|6|6|学习vs中单元测试、性能分析的用法，复习文件使用
|2 | 0 |312|6|12|学习了NABCD模型，学习c多线程
|3 | 0 |312|6|12|
|4 | 0 |312|6|12|
|5 | 0 |312|6|12|