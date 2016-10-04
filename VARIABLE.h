string func_VARIABLE_define_global_var();    //初始化全局变量
string func_VARIABLE_get_var();              //获取变量
string func_VARIABLE_get_global_var();       //获取全局变量
string func_VARIABLE_set_var();              //赋值变量
string func_VARIABLE_set_global_var();       //赋值全局变量
string func_VARIABLE_define_local_var_statement(); //初始化局部变量（语句）
string func_VARIABLE_define_local_var_expression(); //初始化局部变量（表达式）

string func_VARIABLE_define_global_var(){   //(var NAME VALUE)
    get();
    string NAME=eval(),VALUE=eval();
    get();
    return "<block type=\"global_declaration\" id=\""+int2str(id++)+"\" inline=\"false\" x=\"0\" y=\"0\">"+
                "<field name=\"NAME\">"+NAME+"</field>"+
                "<value name=\"VALUE\">"+
                    VALUE+
                "</value>"+
           "</block>";
}
string func_VARIABLE_get_var(){     //(get VAR)
    get();
    string VAR=token->value;
    get();
    get();
    return "<block type=\"lexical_variable_get\" id=\""+int2str(id++)+"\">"+
                "<field name=\"VAR\">"+VAR+"</field>"+
            "</block>";
}
string func_VARIABLE_get_global_var(){  //(global VAR)
    get();
    string VAR=token->value;
    get();
    get();
    return "<block type=\"lexical_variable_get\" id=\""+int2str(id++)+"\">"+
                "<field name=\"VAR\">global "+VAR+"</field>"+
            "</block>";
}
string func_VARIABLE_set_var(){     //(set VAR VALUE)
    get();
    string VAR=token->value;
    get();
    string VALUE=eval();
    get();

    string next=eval();
    return "<block type=\"lexical_variable_set\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<field name=\"VAR\">"+VAR+"</field>"+
                "<value name=\"VALUE\">"+
                    VALUE+
                "</value>"+
                (next==""?"":"<next>"+next+"</next>")+
            "</block>";
}
string func_VARIABLE_set_global_var(){     //(setg VAR VALUE)
    get();
    string VAR=token->value;
    get();
    string VALUE=eval();
    get();

    string next=eval();
    return "<block type=\"lexical_variable_set\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<field name=\"VAR\">global "+VAR+"</field>"+
                "<value name=\"VALUE\">"+
                    VALUE+
                "</value>"+
                (next==""?"":"<next>"+next+"</next>")+
            "</block>";
}
string func_VARIABLE_define_local_var_statement(){  //(lets ((VAR1 VAL1) ...) STATEMENT1 STATEMENT2 STATEMENT3 ...)
    vector<string> VAR,VALUE;
    get();
    get();
    while(token->t_type!=tk_end){
        get();
        VAR.push_back(token->value);
        get();
        VALUE.push_back(eval());
        get();
    }
    get();
    string STATEMENT=eval();
    get();

    string next=eval();
    
    string t1="",t2="";

    for(int i=0;i<VAR.size();i++){
        t1+="<localname name=\""+VAR[i]+"\"></localname>";
        t2+="<field name=\"VAR"+int2str(i)+"\">"+VAR[i]+"</field>"+
            "<value name=\"DECL"+int2str(i)+"\">"+
                VALUE[i]+
            "</value>";  
    }
    return "<block type=\"local_declaration_statement\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<mutation>"+
                    t1+
                "</mutation>"+
                t2+
                "<statement name=\"STACK\">"+
                    STATEMENT+
                "</statement>"+
                (next==""?"":"<next>"+next+"</next>")+
           "</block>";
}
string func_VARIABLE_define_local_var_expression(){ //(lete ((VAR1 VAL1) ...) STATEMENT)
    vector<string> VAR,VALUE;
    get();
    get();
    while(token->t_type!=tk_end){
        get();
        VAR.push_back(token->value);
        get();
        VALUE.push_back(eval());
        get();
    }
    get();
    string STATEMENT=eval();
    get();
    
    string t1="",t2="";

    for(int i=0;i<VAR.size();i++){
        t1+="<localname name=\""+VAR[i]+"\"></localname>";
        t2+="<field name=\"VAR"+int2str(i)+"\">"+VAR[i]+"</field>"+
            "<value name=\"DECL"+int2str(i)+"\">"+
                VALUE[i]+
            "</value>";  
    }

    return "<block type=\"local_declaration_expression\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<mutation>"+
                    t1+
                "</mutation>"+
                t2+
                "<value name=\"RETURN\">"+
                    STATEMENT+
                "</value>"+
           "</block>";
}