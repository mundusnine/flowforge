#include "codegen.h"
#include "knob.h"

void create_command(command_t* command,char* name,OpType type){
    command->name = name;
    command->type = type;
    command->sub_cmds.items = NULL;
    command->sub_cmds.count = 0;
}
void command_add_sub(command_t* command,command_t* sub){
    knob_da_append(&command->sub_cmds,sub);
}
static Knob_String_Builder sb = {0};
char* command_as_string(command_t* command){
    size_t last_size = sb.count;
    sb.count = 0;

    if(command->type == OP_FUNCCALL){
        knob_sb_append_cstr(&sb,command->name);
        knob_sb_append_cstr(&sb,"( ");
        for(int i =0; i < command->sub_cmds.count;++i){
            command_t* cmd = command->sub_cmds.items[i];
            if(cmd->name[0] == 'S' && cmd->name[1] == ':'){
                knob_sb_append_cstr(&sb,"\"");
            }        
            knob_sb_append_cstr(&sb,&cmd->name[2]);// 1 to remove the type, for example: S: for string
            if(cmd->name[0] == 'S' && cmd->name[1] == ':'){
                knob_sb_append_cstr(&sb,"\"");
            }        
            if(i + 1 < command->sub_cmds.count){
                knob_sb_append_cstr(&sb,", ");
            }
        }
        knob_sb_append_cstr(&sb,")");
    }

    if(sb.count < last_size){
        sb.items[sb.count] = '\0';
    }
    sb.items[sb.count] = '\0';
    return sb.items;
}
void gen_code(command_t* root){
    assert(0 && "TODO");
}