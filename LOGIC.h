//逻辑相关函数
string func_LOGIC_true();                     //真
string func_LOGIC_false();                    //假
string func_LOGIC_not();                      //非
string func_LOGIC_equal();                    //等于
string func_LOGIC_and();                      //且
string func_LOGIC_or();                       //或

string func_LOGIC_true(){             //(true)
    get();get();
    return "<block type=\"logic_boolean\" id=\""+int2str(id++)+"\">"+
                "<field name=\"BOOL\">TRUE</field>"+
            "</block>";
}

string func_LOGIC_false(){            //(false)
    get();get();
    return "<block type=\"logic_boolean\" id=\""+int2str(id++)+"\">"+
                "<field name=\"BOOL\">FALSE</field>"+
            "</block>";
}

string func_LOGIC_not(){              //(not A)
    get();
    string A=eval();
    get();
    return "<block type=\"logic_negate\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"BOOL\">"+
                    A+
                "</value>"+
           "</block>";
}

string func_LOGIC_equal(){             //(eq A B)
    get();
    string A=eval(),B=eval();
    get();
    return "<block type=\"logic_compare\" id=\""+int2str(id++)+"\" inline=\"true\">"+
                "<field name=\"OP\">EQ</field>"+
                "<value name=\"A\">"+
                    A+
                "</value>"+
                "<value name=\"B\">"+
                    B+
                "</value>"+
           "</block>";
}

string func_LOGIC_and(){               //(and A B)
    get();
    string A=eval(),B=eval();
    get();
    return "<block type=\"logic_compare\" id=\""+int2str(id++)+"\" inline=\"true\">"+
                "<field name=\"OP\">AND</field>"+
                "<value name=\"A\">"+
                    A+
                "</value>"+
                "<value name=\"B\">"+
                    B+
                "</value>"+
           "</block>";
}

string func_LOGIC_or(){                //(or A B)
    get();
    string A=eval(),B=eval();
    get();
    return "<block type=\"logic_compare\" id=\""+int2str(id++)+"\" inline=\"true\">"+
                "<field name=\"OP\">OR</field>"+
                "<value name=\"A\">"+
                    A+
                "</value>"+
                "<value name=\"B\">"+
                    B+
                "</value>"+
           "</block>";
}