string func_TEXT_text();                     //文本
string func_TEXT_join();                     //合并文本
string func_TEXT_length();                   //求长度
string func_TEXT_is_empty();                 //是否为空
string func_TEXT_cmp();                      //比较文本
string func_TEXT_remove_space();             //删除空格
string func_TEXT_bigger_smaller();           //转换为大写/小写
string func_TEXT_get_pos();                  //求子串在文本中的起始位置
string func_TEXT_is_include();               //检查文本中是否包含子串
string func_TEXT_split_with_sign();          //用分隔符 分解/分解首项/任意分解/分解任意首项 文本
string func_TEXT_split_with_space();         //用空格分割
string func_TEXT_get_from_pos();             //从文本某处开始提取某长度文本
string func_TEXT_replace();                  //将文本中的匹配子串替换
string func_TEXT_obfuscated_text();          //Obfuscated Text

string func_TEXT_text(){    //  (txt TEXT)
    get();
    string TEXT=eval();
    get();
    return  "<block type=\"text\" id=\""+int2str(id++)+"\">"+
                "<field name=\"TEXT\">"+TEXT+"</field>"+
            "</block>";
}
string func_TEXT_join(){    //  (txtJoin A B C D ...)
    get();
    vector<string>join;
    while(token->t_type!=tk_end){
        join.push_back(eval());
    }
    string ADD="";
    for(int i=0;i<join.size();i++){
        ADD+="<value name=\"ADD"+int2str(i)+"\">"+
                    join[i]+
             "</value>";
    }
    get();
    return  "<block type=\"text_join\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<mutation items=\""+int2str(join.size())+"\"></mutation>"+
                ADD+
            "</block>";
}
string func_TEXT_length(){  //  (txtLen A)
    get();
    string A=eval();
    get();
    return  "<block type=\"text_length\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"VALUE\">"+
                    A+
                "</value>"+
            "</block>";
}
string func_TEXT_is_empty(){    //  (txtEmpty A)
    get();
    string A=eval();
    get();
    return  "<block type=\"text_isEmpty\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"VALUE\">"+
                    A+
                "</value>"+
            "</block>";
}
string func_TEXT_cmp(){     //  ([txt< txt= txt>] A B)
    string OP="";
    if(token->value=="txt<")OP="LT";
    else if(token->value=="txt=")OP="EQ";
    else if(token->value=="txt>")OP="GT";
    get();
    string A=eval(),B=eval();
    get();
    return  "<block type=\"text_compare\" id=\""+int2str(id++)+"\" inline=\"true\">"+
                "<field name=\"OP\">"+OP+"</field>"+
                "<value name=\"TEXT1\">"+
                    A+
                "</value>"+
                "<value name=\"TEXT2\">"+
                    B+
                "</value>"+
            "</block>";
}
string func_TEXT_remove_space(){    //(rmSpace A)
    get();
    string A=eval();
    get();
    return  "<block type=\"text_split_at_spaces\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"TEXT\">"+
                    A+
                "</value>"+
            "</block>";
}
string func_TEXT_bigger_smaller(){  //  (changeCase [up down] A)
    get();
    string OP="";
    if(token->value=="up")OP="UPCASE";else if(token->value=="down")OP="DOWN";
    get();
    string A=eval();
    get();
    return  "<block type=\"text_changeCase\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<field name=\"OP\">"+OP+"</field>"+
                "<value name=\"TEXT\">"+
                    A+
                "</value>"+
            "</block>";
}
string func_TEXT_get_pos(){     //  (getPos PIECE TEXT)
    get();
    string PIECE=eval(),TEXT=eval();
    get();
    return  "<block type=\"text_starts_at\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"PIECE\">"+
                    PIECE+
                "</value>"+
                "<value name=\"TEXT\">"+
                    TEXT+
                "</value>"+
            "</block>";
}
string func_TEXT_is_include(){  //  (txtCon TEXT PEICE)
    get();
    string TEXT=eval(),PEICE=eval();
    get();
    return  "<block type=\"text_contains\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"TEXT\">"+
                    TEXT+
                "</value>"+
                "<value name=\"PIECE\">"+
                    PEICE+
                "</value>"+
            "</block>";
}
string func_TEXT_split_with_sign(){     //  (signSplit [SPLIT SPLITATFIRST SPLITATFIRSTOFANY SPLITATANY] TEXT AT)
    get();
    string OP=token->value;
    get();
    string TEXT=eval(),AT=eval();
    get();
    return  "<block type=\"text_split\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<mutation mode=\""+OP+"\"></mutation>"+
                "<field name=\"OP\">"+OP+"</field>"+
                "<value name=\"TEXT\">"+
                    TEXT+
                "</value>"+
                "<value name=\"AT\">"+
                    AT+
                "</value>"+
            "</block>";
}
string func_TEXT_split_with_space(){    //  (spilitSpace TEXT)
    get();
    string TEXT=eval();
    get();
    return  "<block type=\"text_split_at_spaces\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"TEXT\">"+
                    TEXT+
                "</value>"+
            "</block>";
}
string func_TEXT_get_from_pos(){    //  (txtSeg TEXT START LENGTH)
    get();
    string TEXT=eval(),START=eval(),LENGTH=eval();
    get();
    return  "<block type=\"text_segment\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"TEXT\">"+
                    TEXT+
                "</value>"+
                "<value name=\"START\">"+
                    START+
                "</value>"+
                "<value name=\"LENGTH\">"+
                    LENGTH+
                "</value>"+
            "</block>";
}
string func_TEXT_replace(){   //  (txtReplcae TEXT PIECE TARGET)
    get();
    string TEXT=eval(),PIECE=eval(),TARGET=eval();
    get();
    return  "<block type=\"text_replace_all\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"SEGMENT\">"+
                    TEXT+
                "</value>"+
                "<value name=\"TEXT\">"+
                    PIECE+
                "</value>"+
                "<value name=\"REPLACEMENT\">"+
                    TARGET+
                "</value>"+
            "</block>";
}
string func_TEXT_obfuscated_text(){ //(obfuscatedText A)
    get();
    string A=eval();
    get();
    return  "<block type=\"obfuscated_text\" id=\""+int2str(id++)+"\">"+
                "<mutation confounder=\"ervzrikw\"></mutation>"+
                A+
            "</block>";
}