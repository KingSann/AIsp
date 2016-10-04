string func_COND_if0();                      //如果 则执行 或者执行 否则执行
string func_COND_forRange();                 //计数循环
string func_COND_foreach();                  //列表循环
string func_COND_if();                       //如果 则 否则
string func_COND_do();                       //执行模块 返回结果
string func_COND_while();                    //如果真则循环
string func_COND_eval_without_return();      //求值忽略结果
string func_COND_open_screen();              //打开屏幕
string func_COND_open_screen_with_value();   //打开屏幕并传参
string func_COND_get_init_value();           //获取初始值
string func_COND_close_screen();             //关闭屏幕
string func_COND_close_screen_with_value();  //关闭屏幕并返回值
string func_COND_exit();                     //退出程序
string func_COND_get_init_text();            //获取初始文本
string func_COND_close_screen_with_text();   //关闭屏幕并返回文本

string func_COND_if0(){     //(if0 (TEST DO) (TEST DO) ...)
    get();
    vector<string>TEST,DO;
    while(token->t_type!=tk_end){
        get();
        TEST.push_back(eval());
        DO.push_back(eval());
        get();
    }
    get();
    string next=eval();
    string ADD="<mutation elseif=\""+int2str(TEST.size()-1)+"\"></mutation>";
    for(int i=0;i<TEST.size();i++){
        ADD+="<value name=\"IF"+int2str(i)+"\">"+
                TEST[i]+
             "</value>"+
             "<statement name=\"DO"+int2str(i)+"\">"+
                DO[i]+
             "</statement>";
    }
    return  "<block type=\"controls_if\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                ADD+
                (next==""?"":"<next>"+next+"</next>")+
            "</block>";
}
string func_COND_forRange(){    //(forRange VAR START END STEP STATEMENTS)
    get();
    string VAR=eval(),START=eval(),END=eval(),STEP=eval(),STATEMENTS=eval();
    get();
    string next=eval();
    return  "<block type=\"controls_forRange\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<field name=\"VAR\">"+VAR+"</field>"+
                "<value name=\"START\">"+
                    START+
                "</value>"+
                "<value name=\"END\">"+
                    END+
                "</value>"+
                "<value name=\"STEP\">"+
                    STEP+
                "</value>"+
                "<statement name=\"DO\">"+
                    STATEMENTS+
                "</statement>"+
                (next==""?"":"<next>"+next+"</next>")+
            "</block>";
}
string func_COND_foreach(){     //(forEach VAR LIST STATEMENTS)
    get();
    string VAR=eval(),LIST=eval(),STATEMENTS=eval();
    get();
    string next=eval();
    return  "<block type=\"controls_forEach\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<field name=\"VAR\">"+VAR+"</field>"+
                "<value name=\"LIST\">"+
                    LIST+
                "</value>"+
                "<statement name=\"DO\">"+
                    STATEMENTS+
                "</statement>"+
                (next==""?"":"<next>"+next+"</next>")+
            "</block>";
}
string func_COND_if(){      //(if TEST THEN ELSE)
    get();
    string TEST=eval(),THEN=eval(),ELSE=eval();
    get();
    return  "<block type=\"controls_choose\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"TEST\">"+
                    TEST+
                "</value>"+
                "<value name=\"THENRETURN\">"+
                    THEN+
                "</value>"+
                "<value name=\"ELSERETURN\">"+
                    ELSE+
                "</value>"+
            "</block>";
}
string func_COND_do(){  //(do RET STATEMENTS)
    get();
    string RET=eval(),STATEMENTS=eval();
    get();
    return  "<block type=\"controls_do_then_return\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<statement name=\"STM\">"+
                    STATEMENTS+
                "</statement>"+
                "<value name=\"VALUE\">"+
                    RET+
                "</value>"+
            "</block>";
}
string func_COND_while(){   //(while TEST STATEMENTS)
    get();
    string TEST=eval(),STATEMENTS=eval();
    get();
    string next=eval();
    return  "<block type=\"controls_while\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"TEST\">"+
                    TEST+
                "</value>"+
                "<statement name=\"DO\">"+
                    STATEMENTS+ 
                "</statement>"+
                (next==""?"":"<next>"+next+"</next>")+
            "</block>";
}
string func_COND_eval_without_return(){     //      (calcNoRet EXP)
    get();
    string EXP=eval();
    get();
    string next=eval();
    return  "<block type=\"controls_eval_but_ignore\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"VALUE\">"+
                    EXP+
                "</value>"+
                (next==""?"":"<next>"+next+"</next>")+
            "</block>";
}
string func_COND_open_screen(){     //(openScm TEXT)
    get();
    string TEXT=eval();
    get();
    return  "<block type=\"controls_openAnotherScreen\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"SCREEN\">"+
                    TEXT+
                "</value>"+
            "</block>";
}
string func_COND_open_screen_with_value(){      //(openScmValue NAME VALUE)
    get();
    string NAME=eval(),VALUE=eval();
    get();
    return  "<block type=\"controls_openAnotherScreenWithStartValue\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"SCREENNAME\">"+
                    NAME+
                "</value>"+
                "<value name=\"STARTVALUE\">"+
                    VALUE+
                "</value>"+
            "</block>";
}
string func_COND_get_init_value(){  //(getInitValue)
    get();get();
    return "<block type=\"controls_getStartValue\" id=\""+int2str(id++)+"\"></block>";
}
string func_COND_close_screen(){    //(closeScm)
    get();get();
    return  "<block type=\"controls_closeScreen\" id=\""+int2str(id++)+"\" inline=\"false\"></block>";
}
string func_COND_close_screen_with_value(){     //(closeScmValue VALUE)
    get();
    string VALUE=eval();
    get();
    return  "<block type=\"controls_closeScreenWithPlainText\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"SCREEN\">"+
                    VALUE+
                "</value>"+
            "</block>";
}
string func_COND_exit(){    //(exit)
    get();get();
    return  "<block type=\"controls_closeApplication\" id=\""+int2str(id++)+"\" inline=\"false\"></block>";
}
string func_COND_get_init_text(){   //(getInitText)
    get();get();
    return "<block type=\"controls_getPlainStartText\" id=\""+int2str(id++)+"\"></block>";
}
string func_COND_close_screen_with_text(){      //(closeScmText TEXT)
    get();
    string TEXT=eval();
    get();
    return  "<block type=\"controls_closeScreenWithPlainText\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"TEXT\">"+
                    TEXT+
                "</value>"+
            "</block>";
}