string func_COLOR_black();                   //黑色
string func_COLOR_white();                   //白色
string func_COLOR_red();                     //红色
string func_COLOR_pink();                    //粉色
string func_COLOR_orange();                  //橘色
string func_COLOR_yellow();                  //黄色
string func_COLOR_green();                   //绿色
string func_COLOR_cyan();                    //青色
string func_COLOR_blue();                    //蓝色
string func_COLOR_magenta();                  //紫色
string func_COLOR_gray_light();              //浅灰
string func_COLOR_gray();             //中灰
string func_COLOR_gray_dark();              //深灰
string func_COLOR_mix();                     //颜色合成
string func_COLOR_split();                   //色值分解

string func_COLOR_black(){      //(BLACK)
    get();get();
    return "<block type=\"color_black\" id=\""+int2str(id++)+"\">"+
                "<field name=\"COLOR\">#000000</field>"+
           "</block>";
}
string func_COLOR_white(){      //(WHITE)
    get();get();
    return "<block type=\"color_white\" id=\""+int2str(id++)+"\">"+
                "<field name=\"COLOR\">#ffffff</field>"+
           "</block>";
}
string func_COLOR_red(){        //(RED)
    get();get();
    return "<block type=\"color_red\" id=\""+int2str(id++)+"\">"+
                "<field name=\"COLOR\">#ff0000</field>"+
           "</block>";
}
string func_COLOR_pink(){       //(PINK)
    get();get();
    return "<block type=\"color_pink\" id=\""+int2str(id++)+"\">"+
                "<field name=\"COLOR\">#ffafaf</field>"+
           "</block>";
}
string func_COLOR_orange(){     //(ORANGE)
    get();get();
    return "<block type=\"color_orange\" id=\""+int2str(id++)+"\">"+
                "<field name=\"COLOR\">#ffc800</field>"+
           "</block>";
}
string func_COLOR_yellow(){     //(YELLOW)
    get();get();
    return "<block type=\"color_yellow\" id=\""+int2str(id++)+"\">"+
                "<field name=\"COLOR\">#ffff00</field>"+
           "</block>";
}
string func_COLOR_green(){      //(GREEN)
    get();get();
    return "<block type=\"color_green\" id=\""+int2str(id++)+"\">"+
                "<field name=\"COLOR\">#ff00ff</field>"+
           "</block>";
}
string func_COLOR_cyan(){       //(CYAN)
    get();get();
    return "<block type=\"color_cyan\" id=\""+int2str(id++)+"\">"+
                "<field name=\"COLOR\">#00ffff</field>"+
           "</block>";
}
string func_COLOR_blue(){       //(BLUE)
    get();get();
    return "<block type=\"color_blue\" id=\""+int2str(id++)+"\">"+
                "<field name=\"COLOR\">#0000ff</field>"+
           "</block>";
}
string func_COLOR_magenta(){    //(MAGENTA)
    get();get();
    return "<block type=\"color_magenta\" id=\""+int2str(id++)+"\">"+
                "<field name=\"COLOR\">#ff00ff</field>"+
           "</block>";
}
string func_COLOR_gray_light(){ //(GRAYL)
    get();get();
    return "<block type=\"color_light_gray\" id=\""+int2str(id++)+"\">"+
                "<field name=\"COLOR\">#cccccc</field>"+
           "</block>";
}
string func_COLOR_gray(){       //(GRAY)
    get();get();
    return "<block type=\"color_gray\" id=\""+int2str(id++)+"\">"+
                "<field name=\"COLOR\">#888888</field>"+
           "</block>";
}
string func_COLOR_gray_dark(){  //(GRAYD)
    get();get();
    return "<block type=\"color_dark_gray\" id=\""+int2str(id++)+"\">"+
                "<field name=\"COLOR\">#444444</field>"+
           "</block>";
}
string func_COLOR_mix(){        //(rgb 3-items-list)
    get();
    string A=eval();
    get();
    return "<block type=\"color_make_color\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"COLORLIST\">"+
                    A+
                "</value>"+
           "</block>";
}
string func_COLOR_split(){      //(rgbSplit COLOR)
    get();
    string COLOR=eval();
    get();
    return "<block type=\"color_split_color\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"COLOR\">"+
                    COLOR+
                "</value>"+
           "</block>";
}