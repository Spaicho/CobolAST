/* rexx   */                                                     
                                                                 
   address isredit                                               
   'macro'                                                       
   '(pdsdst) = dataset'                                          
   '(cursl,cursc) = cursor'                                      
   '(lastline) = LINENUM .ZLAST'                                 
                                                                 
   say pdsdst                                                    
   say cursl                                                     
   say cursc                                                     
   say lastline                                                  
                                                                 
   argc = 10                                                     
   rawcode = ''                                                  
   option   = 'option'                                           
   main_ret = 0                                                  
   results  = ''                                                 
                                                                 
   do i=1 to lastline                                            
                                                                 
     ligne = ''                                                  
                                                                 
     address isredit '(ligne) = LINE (i)'                        
     say " length of line " i " : " length(ligne)                
                                                                 
     rawcode = rawcode || ligne                                  
                                                                 
                                                                 
   end                                                           
                                                                 
  address tso                                                    
  "alloc file(load) dataset('pref.user.loade') shr reuse"        
                                                                 
  address ispexec "libdef ispllib library id(load) stack"        
                                                                 
                                                                 
   address tso subcom linkpgm                                    
    if rc =0 then                                               
    address linkpgm 'ccc argc cursc cursl rawcode lastline', 
                    'inc_pds option main_ret result'         
 else                                                        
    say "error !"                                            
 /*                                                          
 address ispexec "libdef ispllib"                            
 address tso "free file(load)" */                            
 exit                                                        
