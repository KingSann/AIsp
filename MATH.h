//数学相关

string func_MATH_number();                   //数
string func_MATH_cmp();                      //比较大小
string func_MATH_plus();                     //加法
string func_MATH_sub();                      //减法
string func_MATH_mul();                      //乘法
string func_MATH_div();                      //除法
string func_MATH_pow();                      //次方
string func_MATH_rand_int();                 //任意整数
string func_MATH_rand_float();               //任意小数
string func_MATH_init_rand_seed();           //初始化随机种子
string func_MATH_min_max();                  //最小值最大值
string func_MATH_sqrt();                     //平方根
string func_MATH_abs();                      //绝对值
string func_MATH_neg();                      //相反数
string func_MATH_lgn();                      //自然对方
string func_MATH_e_pow();                    //e的乘方
string func_MATH_4_5();                      //四舍五入
string func_MATH_int_up();                   //就高取整
string func_MATH_int_down();                 //就低取整
string func_MATH_mod();                      //模数余数商数
string func_MATH_sin_cos_tan_arc();          //sin cos tan asin acos atan
string func_MATH_atan2();                    //atan2
string func_MATH_rnd_change();               //角度变换
string func_MATH_num_to_float();             //数字转化为小数形式
string func_MATH_is_number();                 //判断是否是 数字/Dec/Hex/Bin
string func_MATH_num_convert();               //Dec转Hex或Bin以及逆转换

string func_MATH_number(){              //(num A)
    get();
    string A=eval();
    get();
    return "<block type=\"math_number\" id=\""+int2str(id++)+"\">"+
                "<field name=\"NUM\">"+A+"</field>"+
           "</block>";
}
string func_MATH_cmp(){                 //([> >= < <= = !=] A B)
    string OP="";
    if(token->value==">"){
        OP="GT";
    }else if(token->value==">="){
        OP="GTE";
    }else if(token->value=="<"){
        OP="LT";
    }else if(token->value=="<="){
        OP="LTE";
    }else if(token->value=="="){
        OP="EQ";
    }else if(token->value=="!="){
        OP="NEQ";
    }
    get();
    string A=eval(),B=eval();
    get();
    return "<block type=\"math_compare\" id=\""+int2str(id++)+"\" inline=\"true\">"+
                "<field name=\"OP\">"+OP+"</field>"+
                "<value name=\"A\">"+
                    A+
                "</value>"+
                "<value name=\"B\">"+
                    B+
                "</value>"+
           "</block>";
}

string func_MATH_plus(){            //(+ A B C D ...)
    get();
    string str="";
    int tot=0;
    while(token->t_type!=tk_end){
        str+="<value name=\"NUM"+int2str(tot++)+"\">"+
                eval()+
             "</value>";
    }
    get();
    return "<block type=\"math_add\" id=\""+int2str(id++)+"\" inline=\"true\">"+
                "<mutation items=\""+int2str(tot)+"\"></mutation>"+
                str+
           "</block>";
}
string func_MATH_sub(){             //(- A B)
    get();
    string A=eval(),B=eval();
    get();
    return "<block type=\"math_subtract\" id=\""+int2str(id++)+"\" inline=\"true\">"+
                "<value name=\"A\">"+
                    A+
                "</value>"+
                "<value name=\"B\">"+
                    B+
                "</value>"+
           "</block>";
}
string func_MATH_mul(){             //(* A B C D ...)
    get();
    string str="";
    int tot=0;
    while(token->t_type!=tk_end){
        str+="<value name=\"NUM"+int2str(tot++)+"\">"+
                eval()+
             "</value>";
    }
    get();
    return "<block type=\"math_multiply\" id=\""+int2str(id++)+"\" inline=\"true\">"+
                "<mutation items=\""+int2str(tot)+"\"></mutation>"+
                str+
           "</block>";
}
string func_MATH_div(){             //(/ A B)
    get();
    string A=eval(),B=eval();
    get();
    return "<block type=\"math_division\" id=\""+int2str(id++)+"\" inline=\"true\">"+
                "<value name=\"A\">"+
                    A+
                "</value>"+
                "<value name=\"B\">"+
                    B+
                "</value>"+
           "</block>";
}
string func_MATH_pow(){             //(pow A B)
    get();
    string A=eval(),B=eval();
    get();
    return "<block type=\"math_power\" id=\""+int2str(id++)+"\" inline=\"true\">"+
                "<value name=\"A\">"+
                    A+
                "</value>"+
                "<value name=\"B\">"+
                    B+
                "</value>"+
           "</block>";
}
string func_MATH_rand_int(){        //(rint A B)
    get();
    string A=eval(),B=eval();
    get();
    return "<block type=\"math_random_int\" id=\""+int2str(id++)+"\" inline=\"true\">"+
                "<value name=\"FROM\">"+
                    A+
                "</value>"+
                "<value name=\"TO\">"+
                    B+
                "</value>"+
           "</block>";
}
string func_MATH_rand_float(){      //(rfloat)
    get();
    get();
    return "<block type=\"math_random_float\" id=\""+int2str(id++)+"\"></block>";
}
string func_MATH_init_rand_seed(){  //(rset A)
    get();
    string A=eval();
    get();
    string next=eval();
    return "<block type=\"math_random_set_seed\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"NUM\">"+
                    A+
                "</value>"+
                (next=""?"":"<next>"+next+"</next>")+
           "</block>";
}
string func_MATH_min_max(){         //([min max] A B C D ...)
    string OP="";
    if(token->value=="min"){
        OP="MIN";
    }else if(token->value=="MAX"){
        OP="MAX";
    }
    get();
    int tot=0;
    string str="";
    while(token->t_type!=tk_end){
        str+="<value name=\"NUM"+int2str(tot++)+"\">"+
                eval()+
             "</value>";
    }
    get();
    return "<block type=\"math_on_list\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<mutation items=\""+int2str(tot)+"\"></mutation>"+
                "<field name=\"OP\">"+OP+"</field>"+
                str+
           "</block>";
}
string func_MATH_sqrt(){            //(sqrt A)
    get();
    string A=eval();
    get();
    return "<block type=\"math_single\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<field name=\"OP\">ROOT</field>"+
                "<value name=\"NUM\">"+
                    A+
                "</value>"+
           "</block>";
}
string func_MATH_abs(){             //(abs A)
    get();
    string A=eval();
    get();
    return "<block type=\"math_abs\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<field name=\"OP\">ABS</field>"+
                "<value name=\"NUM\">"+
                    A+
                "</value>"+
           "</block>";
}
string func_MATH_neg(){             //(neg A)
    get();
    string A=eval();
    get();
    return "<block type=\"math_neg\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<field name=\"OP\">NEG</field>"+
                "<value name=\"NUM\">"+
                    A+
                "</value>"+
           "</block>";
}
string func_MATH_lgn(){             //(lgn A)
    get();
    string A=eval();
    get();
    return  "<block type=\"math_single\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<field name=\"OP\">LN</field>"+
                "<value name=\"NUM\">"+
                    A+
                "</value>"+
            "</block>";
}
string func_MATH_e_pow(){           //(exp A)
    get();
    string A=eval();
    get();
    return  "<block type=\"math_single\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<field name=\"OP\">EXP</field>"+
                "<value name=\"NUM\">"+
                    A+
                "</value>"+
            "</block>";
}
string func_MATH_4_5(){             //(round A)
    get();
    string A=eval();
    get();
    return  "<block type=\"math_round\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<field name=\"OP\">ROUND</field>"+
                "<value name=\"NUM\">"+
                    A+
                "</value>"+
            "</block>";
}
string func_MATH_int_up(){          //(ceil A)
    get();
    string A=eval();
    get();
    return "<block type=\"math_ceiling\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<field name=\"OP\">CEILING</field>"+
                "<value name=\"NUM\">"+
                    A+
                "</value>"+
           "</block>";
}
string func_MATH_int_down(){        //(floor A)
    get();
    string A=eval();
    get();
    return "<block type=\"math_floor\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<field name=\"OP\">FLOOR</field>"+
                "<value name=\"NUM\">"+
                    A+
                "</value>"+
           "</block>";
}
string func_MATH_mod(){             //([mod rem quo] A B)
    //模 余 商
    string OP="";
    if(token->value=="mod"){
        OP="MODULO";
    }else if(token->value=="rem"){
        OP="REMAINDER";
    }else if(token->value=="quo"){
        OP="QUOTIENT";
    }
    get();
    string A=eval(),B=eval();
    get();
    return "<block type=\"math_divide\" id=\""+int2str(id++)+"\" inline=\"true\">"+
                "<field name=\"OP\">"+OP+"</field>"+
                "<value name=\"DIVIDEND\">"+
                    A+
                "</value>"+
                "<value name=\"DIVISOR\">"+
                    B+
                "</value>"+
           "</block>";

}
string func_MATH_sin_cos_tan_arc(){ //([sin cos tan asin acos atan] A)
    string OP="";
    if(token->value=="sin"){
        OP="SIN";     
    }else if(token->value=="cos"){
        OP="COS";
    }else if(token->value=="tan"){
        OP="TAN";
    }else if(token->value=="asin"){
        OP="ASIN";
    }else if(token->value=="acos"){
        OP="ACOS";
    }else if(token->value=="atan"){
        OP="ATAN";
    }
    get();
    string A=eval();
    get();
    return "<block type=\"math_trig\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<field name=\"OP\">"+OP+"</field>"+
                "<value name=\"NUM\">"+
                    A+
                "</value>"+
           "</block>";
}
string func_MATH_atan2(){       //(atan2 Y X)
    get();
    string Y=eval(),X=eval();
    get();
    return "<block type=\"math_atan2\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"Y\">"+
                    Y+
                "</value>"+
                "<value name=\"X\">"+
                    X+
                "</value>"+
           "</block>";
}
string func_MATH_rnd_change(){  //([rnd2deg deg2rnd] A)
    string OP="";
    if(token->value=="rnd2deg"){
        OP="RADIANS_TO_DEGREES";
    }else if(token->value=="deg2rnd"){
        OP="DEGREES_TO_RADIANS";
    }
    get();
    string A=eval();
    get();
    return "<block type=\"math_convert_angles\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<field name=\"OP\">"+OP+"</field>"+
                "<value name=\"NUM\">"+
                    A+
                "</value>"+
           "</block>";
}
string func_MATH_num_to_float(){    //(toFloat A POS)
    get();
    string A=eval(),POS=eval();
    get();
    return  "<block type=\"math_format_as_decimal\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"NUM\">"+
                    A+
                "</value>"+
                "<value name=\"PLACES\">"+
                    POS+
                "</value>"+
            "</block>";
}
string func_MATH_is_number(){    //([isNum isDec isHex isBin] A)
    string OP="";
    if(token->value=="isNum"){
        OP="NUMBER";
    }else if(token->value=="isDec"){
        OP="BASE10";
    }else if(token->value=="isHex"){
        OP="HEXADECIMAL";
    }else if(token->value=="isBin"){
        OP="BINARY";
    }
    get();
    string A=eval();
    get();
    return "<block type=\"math_is_a_number\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<field name=\"OP\">"+OP+"</field>"+
                "<value name=\"NUM\">"+
                    A+
                "</value>"+
           "</block>";
};                 //判断是否是 数字/Dec/Hex/Bin
string func_MATH_num_convert(){      //([dec2hex hex2dec dec2bin bin2dec] A)
    string OP="";
    if(token->value=="dec2hex"){
        OP="DEC_TO_HEX";
    }else if(token->value=="hex2bin"){
        OP="HEX_TO_DEC";
    }else if(token->value=="dec2bin"){
        OP="DEC_TO_BIN";
    }else if(token->value=="bin2dec"){
        OP="BIN_TO_DEC";
    }
    get();
    string A=eval();
    get();
    return  "<block type=\"math_convert_number\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<field name=\"OP\">"+OP+"</field>"+
                "<value name=\"NUM\">"+
                    A+
                "</value>"+
            "</block>";
}