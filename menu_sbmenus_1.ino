/*
   Menu comm submenu funcional display lcd.
   Placa de Desenvolvimemto Arduino uno
   Autor Rodrigo de Souza Borges
   08/05/2020
   
   Objetivo:
     Esse menu e um pequeno projeto que podera ser implementado em diversas aplicaçoes.
    Ao precionar e soltar a tecla menu ele inicia o processo saindo do void seup e entrado
   no loop.
    Uma vez estando no loop vc chama as funçoes as duas funçoes (selec) e (menu).
    Estando dentro da funçao menu faz a leitura das teclas selecionar para entrar no respectivo submenu
   e cancelar para sair dele.
    Ja estando dentro dos menus quero implatar funcionalidades ex: ativar uma saida fazer leitura de uma condiçao assim
   por diante.
    Observaçao a base desse menu foi extraida da aula 061 curso arduino do wrktis.
*/

//=========================Bibliotecas  Auxiliares=================================
#include <LiquidCrystal.h>                          //biblioteca do display

//============================definiçoes do pinos==================================

#define btMenu   8                                  // muda os menus principais
#define btEntrar 9                                  // entra os submenus
#define btSair   10                                 // sai dos submenus
#define btMais   11                                 // tecla de avanço
#define btMenos  12                                 // tecla de retrocesso
#define dreno    13                                 // saida para vauvula dreno
#define agua     0                                  // saida para vauvula agua
#define vapor    1                                  // saida para vauvula vapor
 
//======================Prototipos das Funçoes Auxiliares===========================

void mudarMenus ();                                 // muda a tela dos menus principais atraves do btnMenu
void mostrarMenus();                                // apresenta a tela selecionada pelo o usuario
void receitas ();                                   // apresentas as receitas para o usuario
void submenuReceitas  ();                           // apresenta os submenus das receitas
void entrarSubmenu (char opcao);                    // entrar no submenu selecionado
void visualizar ();                                 // funçao auxiliar dentro so submenu que executa uma tarefa 
void editar ();                                     // funçao auxiliar dentro so submenu que executa uma tarefa
void criar ();                                      // funçao auxiliar dentro so submenu que executa uma tarefa
void geral ();                                      // apresenta teste de valvulas estados da ios
void configuracoes ();                              // apresenta os parametros de configuraçoes

//============================== Variaveis Globais ==================================
char menu_0 =0x00;                                  // variavel para selecionar a tela menu geral
char menu_1 =0x01;                                  // variavel para selecionar os menus de segundo nivel(submenus)


//========================Flag de controle dos botoes================================

bool flag_btMenu        = 0x00;                    // flag para armazenar o estado do botaoMenu
bool flag_btEntrar      = 0x00;                    // flag para armazenar o estado do botaoEnter
bool flag_btSair        = 0x00;                    // flag para armazenar o estado do botaoSair
bool flag_btMais        = 0x00;                    // flag para armazenar o estado do botaoAvancar
bool flag_btMenos       = 0x00;                    // flag para armazenar o estado do botaoRetroceder



//===============================Hardware do LCD=====================================

LiquidCrystal disp(7,                               // RS no digital 7
                   6,                               // EN no digital 6
                   5,                               // D4 no digital 5
                   4,                               // D5 no digital 4
                   3,                               // D6 no digital 3
                   2);                              // D7 no digital 2

//================================Configuraçoes Iniciais==============================

void setup() 
{
 //=======================configurando os pinos como entradas=========================
  disp.begin(16,2);                                 // inicia o lcd 16x2
  for(char i=8; i<13; i++) pinMode(i, INPUT);       // config pinos como  entradas para os botoes
  //======================iniciando as flags==========================================
  flag_btMenu         = 0x00;                       // inicia a flag limpa (botaoMenu nao foi precionado) 
  flag_btEntrar       = 0x00;                       // inicia a flag limpa (botaoEnter nao foi precionado)
  flag_btSair         = 0x00;                       // inicia a flag limpa (botaoSair nao foi precionado)
  flag_btMais         = 0x00;                       // inicia a flag limpa (botaoAvancar nao foi precionado)
  flag_btMenos        = 0x00;                       // inicia a flag limpa (botaoRetroceder nao foi precionado)
 //=========================configurando os pinos comom saidas========================
  pinMode(dreno, OUTPUT);                           // config o pino d0 como saida
  pinMode(agua,  OUTPUT);                           // config o pino d1 como saida
  pinMode(vapor, OUTPUT);                           // config o pino d13 como saida
 //================iniciando os pinos de saidas em nivel logico baixo=================
  digitalWrite(dreno, LOW);                         // inicia o dreno desligado
  digitalWrite(agua,LOW);                           // inicia o agua desligada
  digitalWrite(vapor,LOW);                          // inicia a vapor desligado 
 //=============================inprimindo a primeira a mensagem======================
  disp.setCursor(0,0);                              // posiciona o cursor na primeira linha
  disp.print("precione");                           // escreve a palavra precione
  disp.setCursor(0,1);                              // posiciona o cursor na primeira coluna e segunda linha
  disp.print("menu...");                            // imprime a palavra menu na tela
  
}// fim setup 

//====================================Funçao Principal=================================

void loop() 
{
  mudarMenus();                                     //chama a funçao para mudança de tela
  mostrarMenus();                                   //mostra a tela selecionada pelo usuario

}// fim do loop


//=========================Desenvolvimento das Funçoes Auxiliares=======================


//==============================Função para mudar as telas==============================

void mudarMenus()
{ 
    if(digitalRead(btMenu))  flag_btMenu = 0x01;        // se o botao menu for precionado seta a flag de controle do botao
    if(!digitalRead(btMenu) && flag_btMenu )            // se o botao for solto e flag estiver em um
    {
      flag_btMenu = 0x00;                               // limpa a flag de controle do botao
      disp.clear();                                     // limpa o display lcd
      menu_0 ++;                                        // incrementa a variavel de controle das telas quando o botaoMenu for solto
      if(menu_0 >3) menu_0 = 0x01;                      // se a variavel menuGeral for maior que 3 retorna a primeira tela
    }//fim if
}// fim mudarMenus


//============================Funnção para visualizar as telas===========================

void mostrarMenus()                                     // visualiza as telas comandadas pela tecla menu
{
     switch (menu_0)
     {
      case 1:
      receitas();                                       // chama funcao para vizualizar as receitas
      break;                                            // que contem outros menus com suas respectivas funçoes 
      
      case 2:
      geral();                                          // chama a funçao para testar saidas
      break;
    
      case 3:
      configuracoes ();                                 // chama a funçao de configurar os parametros
      break;
    
     }//fim switch

}// fim menus_principais

//=====desenvolvimento da funçao receita que faz parte do case 1 dos menus principais======
void receitas()
{
   
    disp.setCursor(0,0);                                // posiciona o cursor na coluna 1 e linha 1
    disp.print("Receitas");                             // inprime a msg "receitas"
    disp.setCursor(0,1);
    disp.print("selc      cancel");
    
    if(digitalRead(btEntrar)) flag_btEntrar = 0x01;     // se o botao entrar for precionado seta a flag de controle
    if(!digitalRead(btEntrar) && flag_btEntrar)           // se o botao entrar for solto e flag de controle setada
    {
        flag_btEntrar = 0x00;                           // limpa a flag de controle
        disp.setCursor(0,1);                            // posiciona o cursor na coluna 1 e linha 1
        disp.clear();
        
        disp.print("selec");                      // inprime a msg "selecioada"
       
        while(true)                                     // entra no laço finito
        {
           submenuReceitas();                           //chama a funçao dos submenus da receita
           if(digitalRead(btSair)) flag_btSair = 0x01;  // se o botao entrar for precionado seta a flag de controle
           if(!digitalRead(btSair) && flag_btSair)      // se o botao entrar for solto e flag de controle setada
           {
              flag_btSair = 0x00;                       // limpa a flag de controle
              break;                                    // comando para sair do laço
            
           }//fin do if sair
           
          
        }//fim do while
         
      
    }//fim do if entrar
    
    
   
}//fim receitas

//====================================funçao a desenvolver===================================
void geral()
{
      disp.setCursor(0,0);                             //posiciona o cursor na coluna 1 e linha 1
      disp.print("geral");                             //imprime na a palavra geral

}//fim geral

//====================================funçao a desenvolver===================================
void configuracoes ()
{
       disp.setCursor(0,0);                             //posiciona o cursor na coluna 1 e linha 1
       disp.print("configuracoes");                     //imprime na a palavra configuracoes

}//fim configuracoes

//=====================navega e apresenta os submenus selecionados============================ 
void submenuReceitas()
{
  
      if(digitalRead(btMais)) flag_btMais   = 0x01;    // se botao mais for precionado seta a flag de controle
      if(digitalRead(btMenos)) flag_btMenos = 0x01;    // se o botao menos for precionado seta a flag de controle
   
      if(!digitalRead(btMais) && flag_btMais)          // se o botao mais for solto e flag setada
      {
          flag_btMais = 0x00;                          // limpa a flag de controle
          disp.clear();                                // limpa o display
          menu_1++;                                    // incrementa a variavel de controle de telas do submenu
          if(menu_1>3) menu_1 = 0x01;                  // se for a variavel for maior que 3 volta a ser um
     
      }//fim do if mais

      if(!digitalRead(btMenos) && flag_btMenos)        // se o botao retroceder for solto e flag setada
      {
          flag_btMenos = 0x00;                         // limpa flag de controle
          disp.clear();                                // limpa o display
          menu_1--;                                    // decrementa em um 
          if(menu_1<1) menu_1 = 0x03;                  // se for menor que 1 volta a ser 3
      
      }//fim do if menos
  

      switch(menu_1) //apresenta as telas 
      {
        case 1:
        disp.setCursor(0,0);                                               //posiciona o cursor na coluna 1 e linha 1
        disp.print("visualizar");                                          //imprime a mensagem visualizar na tela
        disp.setCursor(0,1);                                               //Posiciona cursor na coluna 1, linha 2   
        disp.print("receita");                                             //imprime a mensagem receita na tela
        entrarSubmenu(1);                                                  //chama funçao com parametro 1 para entrar na funçao   
        break;
        
        case 2:
        disp.setCursor(0,0);                                               //posiciona o cursor na coluna 1 e linha 1
        disp.print("editar");                                              //imprime a mensagem editar na tela
        disp.setCursor(0,1);                                               //Posiciona cursor na coluna 1, linha 2   
        disp.print("receita");                                             //imprime a mensagem receita na tela
        entrarSubmenu(2);                                                  //chama funçao com parametro 2 para entrar na funçao 
        break;                                                               
        
        case 3:
        disp.setCursor(0,0);                                               //posiciona o cursor na coluna 1 e linha 1
        disp.print("criar");                                               //imprime a mensagem criar na tela
        disp.setCursor(0,1);                                               //Posiciona cursor na coluna 1, linha 2                       
        disp.print("receita");                                             //imprime a mensagem receita na tela
        entrarSubmenu(3);                                                  //chama funçao com parametro 3 para entrar na funçao 
        break;
      
      }//fim switch
  
}//fim submenuReceitas

//============================funçao con  parametro  para entrar no submenu selecionado======================
void entrarSubmenu (char opcao)
{
       if(digitalRead(btEntrar)) flag_btEntrar = 0x01;       // se o botao entrar for precionado seta a flag de controle
       if(!digitalRead(btEntrar) && flag_btEntrar)           // se o botao entrar for solto e flag for setada
       {
          flag_btEntrar = 0x00;                              // limpa a flag de controle
           
          switch(opcao)                                      // laço com variavel opcao para selecionar a funçao que vai entrar
          {
              case 1:
              visualizar();                                  // chama a funçao visualizar
              break;
    
              case 2:
              editar();                                      // chama a funçao editar
              break;
    
              case 3:
              criar();                                       // chama a funçao criar
              break;
            
             
          }// fim do switch    
        
       }//fim if
  
}//fim entrarSubmenu

//=============================funçao para executar a tarefa==========================
void visualizar ()
{
  
    while(  true )
    {
       
       if(digitalRead(btMais)) flag_btMais = 0x01;           // se o botao mais for precionado seta a flag de controle
       if(digitalRead(btMenos)) flag_btMenos = 0x01;         // se o botao menos for precionado seta a flag de controle
      
       if(!digitalRead(btMais) && flag_btMais)               // se o botao mais for solto e flag setada
       {
          flag_btMais = 0x00;                                // limpa a flag de controle
          disp.clear();                                      // limpa o display
          disp.setCursor(0,0);                               // Posiciona cursor na coluna 1, linha 1
          disp.print("Bomba agua");                          // Imprime mensagem "bomba agua"
          disp.setCursor(0,4);                               // Posiciona cursor na coluna 4, linha 2   
          disp.print("ligada");
          digitalWrite(agua,HIGH);                           // nivel alto no pino d0 
        
       }//fim if mais 

        if(!digitalRead(btMenos) && flag_btMenos)             // se o botao mais for solto e flag setada
       {
          flag_btMenos = 0x00;                                // limpa a flag de controle
          disp.clear();                                       // limpa o display
          disp.setCursor(0,0);                                // Posiciona cursor na coluna 1, linha 1
          disp.print("Bomba agua");                           // Imprime mensagem "bomba agua"
          disp.setCursor(2,1);                                // Posiciona cursor na coluna 2, linha 2   
          disp.print("Desligada");                            // inprime a msg "desligada"
          digitalWrite(agua,LOW);                             // nivel baixo no pino d0 
        
       }//fim if menos 
       
       if(digitalRead(btSair))flag_btSair =0x01;             // se botao sair for precioado seta a flag de controle
       if(!digitalRead(btSair) && flag_btSair)               // se o botao sair for solto e flag setada
       {  
          flag_btSair = 0x00;                                // limpa a flag 
          break;                                             // comando para sair do laço
          disp.clear();
 
       }//fim do if sair
    
    }//fim while 
   
}//fim visualizar

//====================================funçao a desenvolver===================================
void editar ()
{

    while(1)
      {
         disp.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
         disp.print("Tarefa 2");                              //Imprime mensagem
         disp.setCursor(0,1);                                 //Posiciona cursor na coluna 1, linha 2   
         disp.print("Em funcionamento");
      
      }//fim do while
}//fim do editar
//====================================funçao a desenvolver===================================
void criar ()
{

    while(1)
      {
         disp.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
         disp.print("Tarefa 3");                              //Imprime mensagem
         disp.setCursor(0,1);                                 //Posiciona cursor na coluna 1, linha 2   
         disp.print("Em funcionamento"); 
      
      }//fim do while
}//fim do criar
