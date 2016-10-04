
map<string,vector<string> >func_args;

string func_PROC_define_procedure();         //定义过程
string func_PROC_define_function();          //定义函数
string func_PROC_call_proc();                //执行过程
string func_PROC_call_func();                //执行函数

string func_PROC_define_procedure(){    //(defpc NAME (ARG1 ARG2 ...) STATEMENT ...)
    get();
    string NAME=token->value;
    get();
    get();
    vector<string>ARGS;
    while(token->t_type!=tk_end){
        ARGS.push_back(token->value);
        get();
    }
    func_args[NAME]=ARGS;
    get();
    string STATEMENT=eval();
    get();
    while(token->t_type==tk_end){       //权宜之计
        get();
    }
    
    string ret="";
    ret+="<block type=\"procedures_defnoreturn\" id=\""+int2str(id++)+"\" x=\"0\" y=\"0\">";
    ret+="<mutation>";
    for(int i=0;i<ARGS.size();i++){
        ret+="<arg name=\""+ARGS[i]+"\"></arg>";
    }
    ret+="</mutation>";
    ret+="<field name=\"NAME\">"+NAME+"</field>";
    for(int i=0;i<ARGS.size();i++){
        ret+="<field name=\"VAR"+int2str(i)+"\">"+ARGS[i]+"</field>";
    }
    ret+="<statement name=\"STACK\">"+
            STATEMENT+
         "</statement>"+
        "</block>";
    return ret;
}
string func_PROC_define_function(){     //(defun NAME (ARG1 ARG2 ...) VALUE)
    get();
    string NAME=token->value;
    get();
    get();
    vector<string>ARGS;
    while(token->t_type!=tk_end){
        ARGS.push_back(token->value);
        get();
    }
    func_args[NAME]=ARGS;
    get();
    string VALUE=eval();
    get();

    while(token->t_type==tk_end){       //权宜之计
        get();
    }

    string ret="";
    ret+="<block type=\"procedures_defreturn\" id=\""+int2str(id++)+"\" inline=\"false\" x=\"0\" y=\"0\">";
    ret+="<mutation>";
    for(int i=0;i<ARGS.size();i++){
        ret+="<arg name=\""+ARGS[i]+"\"></arg>";
    }
    ret+="</mutation>";
    ret+="<field name=\"NAME\">"+NAME+"</field>";
    for(int i=0;i<ARGS.size();i++){
        ret+="<field name=\"VAR"+int2str(i)+"\">"+ARGS[i]+"</field>";
    }
    ret+="<value name=\"RETURN\">"+
            VALUE+
         "</value>"+
        "</block>";

    return ret;
}
string func_PROC_call_proc(){           //(callp NAME ARG1 ARG2 ...)
    get();
    string NAME=token->value;
    get();
    vector<string>ARGS;
    while(token->t_type!=tk_end){
        ARGS.push_back(eval());
    }
    get();

    string next=eval();
    
    vector<string> &arg=func_args[NAME];
    string ret="";
    ret+="<block type=\"procedures_callnoreturn\" id=\""+int2str(id++)+"\">"+
            "<mutation name=\""+NAME+"\">";
    for(int i=0;i<arg.size();i++){
        ret+="<arg name=\""+arg[i]+"\"></arg>";
    }
    ret+="</mutation><field name=\"PROCNAME\">"+NAME+"</field>";
    for(int i=0;i<ARGS.size();i++){
        ret+="<value name=\"ARG"+int2str(i)+"\">"+ARGS[i]+"</value>";
    }
    ret+=(next==""?"":"<next>"+next+"</next>")+"</block>";
    return ret;
}
string func_PROC_call_func(){           //(callf NAME ARG1 ARG2 ...)
    get();
    string NAME=token->value;
    get();
    vector<string>ARGS;
    while(token->t_type!=tk_end){
        ARGS.push_back(eval());
    }
    get();
    vector<string> &arg=func_args[NAME];
    string ret="";
    ret+="<block type=\"procedures_callreturn\" id=\""+int2str(id++)+"\" inline=\"false\">"+
            "<mutation name=\""+NAME+"\">";
    for(int i=0;i<arg.size();i++){
        ret+="<arg name=\""+arg[i]+"\"></arg>";
    }
    ret+="</mutation><field name=\"PROCNAME\">"+NAME+"</field>";
    for(int i=0;i<ARGS.size();i++){
        ret+="<value name=\"ARG"+int2str(i)+"\">"+ARGS[i]+"</value>";
    }
    ret+="</block>";
    return ret;
}