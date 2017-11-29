## stringCount

### History
- 2017-11-10
complete basic function base on Class StrBox, StrCount
- 2017-11-20
test jsoncpp library
- 2017-11-27 to 2017-11-29
    1. Optimize the source code structure
    2. source code is store in src directory
    3. StrBox and StrCount are discarded, using StrMap
    4. Abort jsoncpp, use RapidJSON, **add new feature: support JSON output**
    5. rewrite the makefile, one is in src, one is out of src
    6. to build stringCount, just run **make** out of **src** 

### Introduction
**Question**
```
由A~J 10个字母组成的随机字符，长度度1~5，共1000000个
不考虑字母出现的顺序，将具有相同字母的字符串归类
给出总共有多少类字符 ，每类的数总是多少
```
1. 针对上述问题，我们用一个64bit 数来作为一个真值表，基于如下映射：

|Bit|0|1|2|3|4|...|25|26|...|51|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|**Character**|A|B|C|D|E|...|Z|a|...|z|
对应位为1时表示字符串中出现了该字母，用这样一个数来表示一个字符串的特征

2. 构建一个StrMap类，该类支持通过 **add(const string&)** 函数直接添加一个字符串到一个StrMap的实例中，并完成自动统计。

3. 为了更好地展示结果，除了输出txt格式的文件外，基于RapidJSON，输出格式化的JSON文件。
RapidJSON只能输出无格式化JSON文件，可读性差；StrMap的 **printJSONResult()** 函数支持格式化的JSON输出。

### stringCount feature
- 支持统计任意长度的字符串，支持检索A～Z、a～z共52个字母。
- 支持输出格式化好的JSON文件

### Option
```
Usage: String Statistics Program
        -h      Print this usage.
        -f      The file to analyze.
        -g      Generate a sample file
        -o      The file to store the result.
```

