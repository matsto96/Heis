# Heis
# set_speed -> somthing else, check elev.c
# void changeDir();
  If(currentDir = dir_up){
  currentDir = dir_down;
  else{
  currentDir = dir_up;}}
# void check_all();
# void getNext(currentDir);
  Funksjoner: void check_dir(currentDir); 
          If(no update){
          changeDir();}
  Variabler: Limit case currentDir, dir_up and dir_down
  
Ide
  switch (currentDir)
  case (currentDir != Idle){
      getNext(currentDir);
      
  case default //idle
