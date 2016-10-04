#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <map>

using namespace std;


FILE *in,*out;

unsigned int id=1;

enum TOKEN_TYPE{
    tk_none,        //未知
    tk_symbol,      //符号
    tk_num,         //数字
    tk_string,      //字符串
    tk_beg,         //左括号
    tk_end,         //右括号
    tk_false,       //假 
    tk_true         //真
};

struct TOKEN{
    TOKEN_TYPE t_type;
    string value;
    TOKEN *next;
    TOKEN(){
        t_type=tk_none;
        next=NULL;
    }
}*head,*cur,*token;


map<string,string (*) (void)>funcs;

void init();
void error(string s);                        //报错
void token_getall();                         //获取所有token
string eval();                               //从当前token执行一个表达式
void get();                                  //获取下一个token
string int2str(int a);                       //int转string


//AI的一些内置函数

#include "COND.h"
#include "LOGIC.h"
#include "MATH.h"
#include "TEXT.h"
#include "LIST.h"
#include "COLOR.h"
#include "VARIABLE.h"
#include "PROC.h"
#include "WIDGET.h"


void init(){
    head=(TOKEN*)malloc(sizeof(TOKEN));
    cur=head;
    token=head;

    //funcs[str]=
    funcs["defun"]=func_PROC_define_function;
    funcs["defpc"]=func_PROC_define_procedure;
    funcs["callf"]=func_PROC_call_func;
    funcs["callp"]=func_PROC_call_proc;

    funcs["emList"]=func_LIST_empty_list;
    funcs["list"]=func_LIST_create_with;
    funcs["addItem"]=func_LIST_add_item;
    funcs["getItem"]=func_LIST_get_item;
    funcs["len"]=func_LIST_length;
    funcs["append"]=func_LIST_append_item;
    funcs["insert"]=func_LIST_insert_item;
    funcs["copy"]=func_LIST_copy;
    funcs["remove"]=func_LIST_remove_item;
    funcs["del"]=func_LIST_del_item;

    funcs["letS"]=func_VARIABLE_define_local_var_statement;
    funcs["letE"]=func_VARIABLE_define_local_var_expression;
    funcs["defvar"]=func_VARIABLE_define_global_var;
    funcs["global"]=func_VARIABLE_get_global_var;
    funcs["setg"]=func_VARIABLE_set_global_var;

    funcs["forEach"]=func_COND_foreach;
    funcs["for"]=func_COND_forRange;
    funcs["withRet"]=func_COND_do;
    funcs["cond"]=func_COND_if0;
    funcs["if"]=func_COND_if;
    funcs["exit"]=func_COND_exit;
    
    funcs["set"]=func_VARIABLE_set_var;
    funcs["get"]=func_VARIABLE_get_var;

    funcs["+"]=func_MATH_plus;
    funcs["-"]=func_MATH_sub;
    funcs["*"]=func_MATH_mul;
    funcs["/"]=func_MATH_div;
    funcs["neg"]=func_MATH_neg;

    funcs[">"]=func_MATH_cmp;
    funcs[">="]=func_MATH_cmp;
    funcs["<"]=func_MATH_cmp;
    funcs["<="]=func_MATH_cmp;
    funcs["="]=func_MATH_cmp;
    funcs["!="]=func_MATH_cmp;

    funcs["setRandSeed"]=func_MATH_init_rand_seed;
    funcs["randRange"]=func_MATH_rand_int;

    funcs["s<"]=func_TEXT_cmp;
    funcs["s="]=func_TEXT_cmp;
    funcs["s>"]=func_TEXT_cmp;

    funcs["true"]=func_LOGIC_true;
    funcs["false"]=func_LOGIC_false;
    funcs["equal"]=func_LOGIC_equal;
    funcs["and"]=func_LOGIC_and;
    funcs["or"]=func_LOGIC_or;
    funcs["not"]=func_LOGIC_not;
}

void error(string s){
    cout<<s<<endl;
    exit(0);
}

void token_getall(){
    while(!feof(in)){
        char c=fgetc(in);

        if(feof(in))
            return;
        if(c==';'){         //注释
            while(c!='\n'&&c!='\r'){
                c=fgetc(in);
            }
            continue;
        }else if(c==' '||c=='\t'||c=='\n'||c=='\r'){
            continue;
        }else if(c=='('||c=='['){                               //begin sign
            cur->t_type=tk_beg;
            cur->value="(";
        }else if(c==')'||c==']'){                               //end sign
            cur->t_type=tk_end;
            cur->value=")";
        }else if(c=='\"'){                                      //string
            cur->t_type=tk_string;
            string str;
            c=fgetc(in);
            while(c!='\"'){
                if(c=='\\'){
                    switch(fgetc(in)){
                        case '0':str+='\0';break;
                        case 'a':str+='\a';break;
                        case 'b':str+='\b';break;
                        case 't':str+='\t';break;
                        case 'n':str+='\n';break;
                        case 'v':str+='\v';break;
                        case 'f':str+='\f';break;
                        case 'r':str+='\r';break;
                        case '\"':str+='\"';break;
                        case '\'':str+='\'';break;
                        case '\\':str+='\\';break;
                        default:error("Unknow Trans-Mean-Char");
                    }
                }else{
                    str+=c;
                }
                c=fgetc(in);
            }
            cur->value=str;
        }else if(c>='0'&&c<='9'){                               //number
            cur->t_type=tk_num;
            string str;
            while((c>='0'&&c<='9')||c=='.')
                str+=c,c=fgetc(in);
            ungetc(c,in);
            cur->value=str;
        }else if(c=='#'){
            c=fgetc(in);
            if(c=='f')
                cur->t_type=tk_false,cur->value="#f";
            else if(c=='t')
                cur->t_type=tk_true,cur->value="#t";
            else    
                error("Unknow Char, choose #t or #f");
        }else if(c!=' '&&c!='\t'&&c!='\n'&&c!='\r'){        //symbol
            cur->t_type=tk_symbol;
            string str;

            while(c!=' '&&c!='\t'&&c!='\n'&&c!='\r'&&c!='('&&c!=')')
                str+=c,c=fgetc(in);
            ungetc(c,in);
            cur->value=str;
        }else{
            string er="Unknow Char: ";
            er+=c;
            error(er);
        }
        cur->next=(TOKEN*)malloc(sizeof(TOKEN));
        cur=cur->next;
    }
}

void get(){
    if(token->next==NULL)error("NULL");
    token=token->next;
}

string int2str(int a){
    string ret="";
    do
        ret+=(a%10)+'0';
    while (a/=10);
    reverse(ret.begin(),ret.end());
    return ret;
}

string eval(){
    string ret="";
    if(token==cur)return ret;

    cout<<"TOKEN: "<<(token->value)<<endl;

    if(token->t_type==tk_beg){
        get();
        string type=token->value;
        cout<<"TYPE: "<<type<<endl;
        if(funcs.count(type)){  //内置函数
            ret=funcs[type]()+"\n";
        }
    }else if(token->t_type==tk_end){
        //get();
        return "";
    }else if(token->t_type==tk_num){
        ret="<block type=\"math_number\" id=\""+int2str(id++)+"\">"+
                "<field name=\"NUM\">"+token->value+"</field>"+
             "</block>";
        get();
    }else if(token->t_type==tk_false){
        ret="<block type=\"logic_boolean\" id=\""+int2str(id++)+"\" x=\"0\" y=\"0\">"+
                "<field name=\"BOOL\">FALSE</field>"+
             "</block>";
        get();
    }else if(token->t_type==tk_true){
        ret="<block type=\"logic_boolean\" id=\""+int2str(id++)+"\" x=\"0\" y=\"0\">"+
                "<field name=\"BOOL\">TRUE</field>"+
             "</block>";
        get();
    }else if(token->t_type==tk_symbol){
        ret="<block type=\"lexical_variable_get\" id=\""+int2str(id++)+"\">"+
                "<field name=\"VAR\">"+token->value+"</field>"+
            "</block>";
        get();
    }else if(token->t_type==tk_string){
        ret="<block type=\"text\" id=\""+int2str(id++)+"\">"+
                "<field name=\"TEXT\">"+token->value+"</field>"+
            "</block>";
        get();
    }else{
        error("Eval Error: "+token->value);
    }
    return ret;
}


int main(int argc,char *argv[]){
    if(argc!=3)
        error("Uses \"Lisp2AI [Input File] [Output File]\"");
    in=fopen(argv[1],"rb");
    out=fopen(argv[2],"wb");
    if(in==NULL||out==NULL)error("Open File Error");
    init();
    

    token_getall();
    cout<<"Lexical Over"<<endl;
    
    for(TOKEN *i=head;i!=cur;i=i->next){
        printf("%d %s\n",i->t_type,i->value.c_str());
    }

    string str="";
    str+="<xml xmlns=\"http://www.w3.org/1999/xhtml\">";
    while(token!=cur){
        str+=eval();
    }
    str+="<yacodeblocks ya-version=\"157\" language-version=\"20\"></yacodeblocks>";
    str+="</xml>";
    fputs(str.c_str(),out);
    //cout<<str<<endl;

    cout<<"Parser Over"<<endl;

    fclose(in);
    fclose(out);

    return 0;
}
