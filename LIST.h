string func_LIST_empty_list();               //创建空列表
string func_LIST_create_with();              //创建列表带有初始值
string func_LIST_add_item();                 //添加列表项
string func_LIST_has_item();                 //检查是否存在某个项
string func_LIST_length();                   //长度
string func_LIST_is_empty();                 //是否为空
string func_LIST_rand_choose();              //随机选择
string func_LIST_item_pos();                 //元素位置
string func_LIST_get_item();                 //选择元素（index）
string func_LIST_insert_item();              //插入元素（index）
string func_LIST_replace_item();             //替换元素（index）
string func_LIST_remove_item();              //删除元素（index） LIST INDEX
string func_LIST_del_item();                 //删除元素（index） INDEX LIST
string func_LIST_append_item();              //追加元素
string func_LIST_copy();                     //复制列表
string func_LIST_is_list();                  //是否是列表
string func_LIST_list_to_CSVRow();           //列表转CSV行
string func_LIST_list_to_CSV();              //列表转CSV
string func_LIST_CSVRow_to_list();           //CSV行转列表
string func_LIST_CSV_to_list();              //CSV转列表
string func_LIST_find_key();                 //键值中找关键字


string func_LIST_empty_list(){      //(emlist)
    get();
    get();
    return "<block type=\"lists_create_with\" id=\""+int2str(id++)+"\">"+
                "<mutation items=\"0\"></mutation>"+
            "</block>";
}
string func_LIST_create_with(){     //(list val1 val2 val3 ...)
    string ret="";
    get();
    vector<string>v;
    while(token->t_type!=tk_end)
        v.push_back(eval());
    ret+="<block type=\"lists_create_with\" id=\""+int2str(id++)+"\" inline=\"false\">"+
            "<mutation items=\""+int2str(v.size())+"\"></mutation>";
    for(int i=0;i<v.size();i++){
        ret+="<value name=\"ADD"+int2str(i)+"\">"+
                v[i]+
             "</value>";
    }
    ret+="</block>";
    get();
    return ret;
}
string func_LIST_add_item(){     //(addItem LIST item1 item2 ...)
    get();
    string LIST=eval();
    vector<string>item;
    while(token->t_type!=tk_end){
        item.push_back(eval());
    }
    get();

    string ADD="";
    for(int i=0;i<item.size();i++){
        ADD+="<value name=\"ITEM"+int2str(i)+"\">"+
                item[i]+
             "</value>";    
    }

    string next=eval();

    return  "<block type=\"lists_add_items\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<mutation items=\""+int2str(item.size())+"\"></mutation>"+
                "<value name=\"LIST\">"+
                    LIST+
                "</value>"+
                ADD+
                (next==""?"":"<next>"+next+"</next>")+
            "</block>";
}
string func_LIST_has_item(){     //(listCon LIST ITEM)
    get();
    string LIST=eval(),ITEM=eval();
    get();
    return  "<block type=\"lists_is_in\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"LIST\">"+
                    LIST+
                "</value>"+
                "<value name=\"ITEM\">"+
                    ITEM+
                "</value>"+
            "</block>";
}
string func_LIST_length(){      //(listLen LIST)
    get();
    string LIST=eval();
    get();
    return "<block type=\"lists_length\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"LIST\">"+
                    LIST+
                "</value>"+
            "</block>";
}
string func_LIST_is_empty(){        //(listEmp LIST)
    get();
    string LIST=eval();
    get();
    return "<block type=\"lists_is_empty\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"LIST\">"+
                    LIST+
                "</value>"+
            "</block>";
}
string func_LIST_rand_choose(){     //(listRnd LIST)
    get();
    string LIST=eval();
    get();
    return  "<block type=\"lists_pick_random_item\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"LIST\">"+
                    LIST+
                "</value>"+
            "</block>";
}
string func_LIST_item_pos(){    //(itemPos ITEM LIST)
    get();
    string ITEM=eval(),LIST=eval();
    get();
    return  "<block type=\"lists_position_in\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"ITEM\">"+
                    ITEM+
                "</value>"+
                "<value name=\"LIST\">"+
                    LIST+
                "</value>"+
            "</block>";
}
string func_LIST_get_item(){    //(selIndex LIST NUM)
    get();
    string LIST=eval(),NUM=eval();
    get();
    return  "<block type=\"lists_select_item\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"LIST\">"+
                    LIST+
                "</value>"+
                "<value name=\"NUM\">"+
                    NUM+
                "</value>"+
            "</block>";
}
string func_LIST_insert_item(){     //(insert LIST INDEX ITEM)
    get();
    string LIST=eval(),INDEX=eval(),ITEM=eval();
    get();
    string next=eval();

    return  "<block type=\"lists_insert_item\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"LIST\">"+
                    LIST+
                "</value>"+
                "<value name=\"INDEX\">"+
                    INDEX+
                "</value>"+
                "<value name=\"ITEM\">"+
                    ITEM+
                "</value>"+
                (next==""?"":"<next>"+next+"</next>")+
            "</block>";
}
string func_LIST_replace_item(){    //(listReplace LIST NUM ITEM)
    get();
    string LIST=eval(),NUM=eval(),ITEM=eval();
    get();
    string next=eval();

    return  "<block type=\"lists_replace_item\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"LIST\">"+
                    LIST+
                "</value>"+
                "<value name=\"NUM\">"+
                    NUM+
                "</value>"+
                "<value name=\"ITEM\">"+
                    ITEM+
                "</value>"+
                (next==""?"":"<next>"+next+"</next>")+
            "</block>";
}
string func_LIST_remove_item(){     //(rmListIndex list index)
    string ret="";
    get();
    string list=eval(),index=eval();
    get();
    string next=eval();
    ret="<block type=\"lists_remove_item\" id=\""+int2str(id++)+"\" inline=\"false\">"+
            "<value name=\"LIST\">"+
                list+
            "</value>"+
            "<value name=\"INDEX\">"+
                index+
            "</value>";
    if(next!=""){
        ret+="<next>"+next+"</next>";
    }
    ret+="</block>";
    return ret;
}
string func_LIST_del_item(){     //(delListIndex index list)
    string ret="";
    get();
    string index=eval(),list=eval();
    get();
    string next=eval();
    ret="<block type=\"lists_remove_item\" id=\""+int2str(id++)+"\" inline=\"false\">"+
            "<value name=\"LIST\">"+
                list+
            "</value>"+
            "<value name=\"INDEX\">"+
                index+
            "</value>"+
            (next==""?"":"<next>"+next+"</next>")+
         "</block>";
    return ret;
}
string func_LIST_append_item(){ //(append LIST1 LIST0)
    get();
    string LIST1=eval(),LIST0=eval();
    get();
    string next=eval();

    return  "<block type=\"lists_append_list\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"LIST1\">"+
                    LIST1+
                "</value>"+
                "<value name=\"LIST0\">"+
                    LIST0+
                "</value>"+
                (next==""?"":"<next>"+next+"</next>")+
            "</block>";
}
string func_LIST_copy(){    //(copy LIST)
    get();
    string LIST=eval();
    get();
    return  "<block type=\"lists_copy\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"LIST\">"+
                    LIST+
                "</value>"+
            "</block>";
}
string func_LIST_is_list(){     //(isList EXP)
    get();
    string EXP=eval();
    get();
    return  "<block type=\"lists_is_list\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"ITEM\">"+
                    EXP+
                "</value>"+
            "</block>";
}
string func_LIST_list_to_CSVRow(){  //(List2CSVROW LIST)
    get();
    string LIST=eval();
    get();
    return  "<block type=\"lists_to_csv_row\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"LIST\">"+
                    LIST+
                "</value>"+
            "</block>";
}
string func_LIST_list_to_CSV(){     //(List2CSV LIST)
    get();
    string LIST=eval();
    get();
    return  "<block type=\"lists_to_csv_table\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"LIST\">"+
                    LIST+
                "</value>"+
            "</block>";
}
string func_LIST_CSVRow_to_list(){  //(CSVROW2List TEXT)
    get();
    string TEXT=eval();
    get();
    return  "<block type=\"lists_from_csv_row\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"TEXT\">"+
                    TEXT+
                "</value>"+
            "</block>";
}
string func_LIST_CSV_to_list(){     //(CSV2List TEXT)
    get();
    string TEXT=eval();
    get();
    return  "<block type=\"lists_from_csv_table\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"TEXT\">"+
                    TEXT+
                "</value>"+
            "</block>";
}
string func_LIST_find_key(){    //(lookUp LIST KEY NOTFOUND)
    get();
    string LIST=eval(),KEY=eval(),NOTFOUND=eval();
    get();
    return  "<block type=\"lists_lookup_in_pairs\" id=\""+int2str(id++)+"\" inline=\"false\">"+
                "<value name=\"LIST\">"+
                    LIST+
                "</value>"+
                "<value name=\"KEY\">"+
                    KEY+
                "</value>"+
                "<value name=\"NOTFOUND\">"+
                    NOTFOUND+
                "</value>"+
            "</block>";
}