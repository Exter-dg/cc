
import re
import operator

def getOP(op):
    return {
        '+' : operator.add,
        '-' : operator.sub,
        '*' : operator.mul,
        '/' : operator.truediv ,
        '%' : operator.mod,
        '^' : operator.xor,
        }[op]
def evalBinary(op1, oper, op2):
    op1,op2 = int(op1), int(op2)
    return getOP(oper)(op1, op2)

value_table=dict() 
f = open("input","r")
text = f.readlines()
for i in range(len(text)):

    if '=' in text[i] and not '==' in text[i]: 
        expr = text[i].strip().split('=')
        #print(Assignexpr)
        variable=expr[0]
        
        if ':' in expr[0]: 
            lhs=expr[0].replace(" ","").split(":")
            variable=lhs[1]
            #print value_table
            value_table={}

        var_list=re.split('\+|-|\*|/|%', expr[1])

        if len(var_list)==1:
            if var_list[0].isdigit():
                value_table[variable]=var_list[0]                 
            else:
                if var_list[0] in value_table.keys():
                    expr[1]=value_table[var_list[0]] 
            print (str(expr[0])+'='+str(expr[1]))
    
        if len(var_list)==2: #Case 3
            constant_value="NOCHANGE"
            op1 = var_list[0]
            op2 = var_list[1]
            if '+' in text[i]:
                op='+'
            if '-' in text[i]:
                op='-'
            if '*' in text[i]:
                op='*'
            if '/' in text[i]:
                op='/'
            if op1.isdigit() and op2.isdigit():    
                constant_value=evalBinary(op1, op, op2)
                value_table[expr[0]]=constant_value
            if op1.isdigit() and op2.isdigit()!=1: 
                if op2 in value_table.keys():
                    constant_value=evalBinary(op1, op, value_table[op2])
                    value_table[expr[0]]=constant_value
                
            if op1.isdigit()!=1 and op2.isdigit():# Type 3 - op1 is variable op2 is digit
                if op1 in value_table.keys():
                    constant_value=evalBinary(value_table[op1], op, op2)
                    value_table[expr[0]]=constant_value
              
            if op1.isdigit()!=1 and op2.isdigit()!=1: # Type 4 - op1 is variable op2 is variable
                if op1 in value_table.keys():
                    if op2 in value_table.keys():
                        constant_value=evalBinary(value_table[op1], op, value_table[op2])
                        value_table[expr[0]]=constant_value
                    else: #only op1 in constant table 
                        expr[1]=str(value_table[op1])+str(op)+str(op2)
                elif op2 in value_table.keys():
                    expr[1]=str(op1)+str(op)+str(value_table[op2])
            if constant_value!="NOCHANGE":
                expr[1]=constant_value
            print (str(expr[0])+'='+str(expr[1]))
    elif ':' in text[i]:
        value_table={}
        print(text[i])
    else:
        print(text[i])  

