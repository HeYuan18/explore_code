# JSON简介 #
### 学习目的： ###
<p>
    <pre><code><b>
        1. 掌握并且能使用JSON数据格式进行通信交互;
        2. 理解JSON数据格式和serialize序列化、XML以及数组的区别;
   </b> </code></pre>
</p>

### JSON起源： ###
<p>
    <pre><code><b>
        21世纪初，Douglas Crockford寻找一种简便的数据交换格式，能够在服务器之间交互数据。
        当时通用的数据交换语言是XML，但是Douglas Crockford觉得XML的生成和解析都太麻烦，
        所以他提出了一种简化格式，也就是JSON。
        第一种类型是标量(scalar)，也就是一个单独的字符串或数字；
        第二种类型是序列(sequence),也就是若干个相关的数据按照一定顺序并列在一起，
         又叫做数组(array)或(list)；
        第三种类型是映射(mapping)，也就是一个键/值对(key/value)，即数据有一个名称，
        还有一个与之对应的值，这又称作散列(hash)或字典(dictionary)；
    </b></code></pre>
</p>

### 什么是JSON： ###
<p>
    <pre><code><b>
        JSON就是(JavaScript Object Notation)，它是一种轻量级的数据交换格式;
    </b></code></pre>
</p>

### JSON的基本语法： ###
<p><b>JSON的四个基本规则</b>
    <pre><code><b>
        1. 并列的数据之间用逗号','分隔开;
        2. 映射用冒号':'表示，键值对;
        3. 并列的数据集合(数组)用方括号'[]'表示;
        4. 映射的集合(对象)用大括号'｛｝'表示;
   </b></code></pre>
</p>

### JSON的优点和缺点： ###
<p>
    <pre><code><b>
        JSON的优点:
            1. 数据格式比较简单，易于读写，格式都是压缩的，占用带宽小;
            2. 支持多种语言，包括ActionScript, C, C#, ColdFusion, Java, 
                JavaScript, Perl, PHP, Python, Ruby等服务器端语言，便于服务器端的解析；
        JSON的缺点:
            1.　要求字符集必须是Unicode,受约束性强;
            2.　语法过于严谨，必须遵循JSON语法四个原则;
    </b></code></pre>
</p>

### 相提并论： ###
<p>
    <pre><code><b>
        XML:
            XML是标准通用标记语言(SGML)的子集，非常适合Web传输；
            XML提供统一的方法来描述和交换独立于应用程序或供应商的机构化数据;
        JSON:
            JSON是基于JavaScript Programming Language, Standard ECMA-262 3rd Edition
             -December 1999 的一个子集;
        Serialize:
            Serialize是一种类似于JSON的数据格式，但是PHP的Serialize是将变量序列化，
             返回一个具有变量类型和结构的字符串表达式;
        Array():
            基本数据类型，不能用于数据的传输和交替;
    </b></code></pre>
</p>

# 怎么使用JSON #

# JSON实战(一) #

# JSON实战(二) #

# JSON使用过程中的常见错误 #

