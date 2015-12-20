/* rexx   */                                                      
                                                                  
   address isredit                                                
   'macro'                                                        
   '(pdsdst) = dataset'                                           
   '(cursl,cursc) = cursor'                                       
                                                                  
   say pdsdst                                                     
   say cursl                                                      
   say cursc                                                      
                                                                  
   argc = 10                                                      
   src_file = pdsdst                                              
   option   = 'option'                                            
   main_ret = 0                                                   
   results  = ''                                                  
                                                                  
  address tso                                                     
  "alloc file(load) dataset('pref.user.loade') shr reuse"         
  address ispexec "libdef ispllib library id(load) stack"         
                                                                  
   subcom linkpgm                                                 
                                                                  
   if rc =0 then                                                  
      address linkpgm 'ccc argc cursl cursc src_file',            
                      'inc_pds option main_ret result'            
   else                                                           
      say "error !"                                               
                                                                  
   address ispexec "libdef ispllib"                               
   address tso "free file(load)"                                  
   exit                                                           
