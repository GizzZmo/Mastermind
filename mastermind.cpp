/*
Fil:		Masterminded.cpp
Tittel:     Innleveringsoppgave 1a og b
Kurs:		Procedurell programmering
Levert av:	Jon Arve Ovesen
Dato:		28.februar 2008

/************************************************************************************************
*   Denne C++ koden kallt "Masterminded" er laget med Visual C++ Studio 2008 Express Edition.   *
*                              Spillet er laget for dos.					*
*												*												*
*               Spillet går ut på å gjette de fire pinnenes farge og sekvens.			*
*                         Fargene er representert av tall.					*
*												*												*
*                   Svart pinne betyr at det er rett tall på riktig plass.			*
*                  Hvit pinne betyr at du har rett tall men på feil plass.			*
*												*												*
*                                  a06jonov@his.se						*                         
*		           Laget av Jon Arve Ovesen i 2007-2008					*												*
*************************************************************************************************/
/*
 
 Kompilator direktiver og globale deklarasjoner:

  1. Her inkluderes iostream siden jeg skal bruke funksjoner i dette bibloteket som bla. cin (istream), 
     og cout (ostream). 
  
  2. Inkludering av stdlib header siden jeg skal bruke srand funksjonen. 
     Se https://www.geeksforgeeks.org/time-function-in-c/ for mer info. 
  
  3. Inkludering av header filen time siden jeg skal bruke klokken i systemet til random pseudo 
    generator. Se https://www.geeksforgeeks.org/time-function-in-c/ om denne. 
  
  4. Inkludering av header filen iodos, siden jeg skal vil ha støtte for øæå.
  
  5. Definisjon av antall_farger slik at man kan gjøre spillet lettere eller vanskligere
  
  6. Definisjon av maks_antall_omganger, som er en annen måte å gjøre spillet lettere eller vanskligere.
  
  7. Siden alle filene i standardiserte C++ bibloteket er deklarerte i std namespace, 
	 slipper jeg unna med å benevne denne deklarasjonen uten å spesifisere nærmere. */

#include <iostream> 
#include <stdlib.h> 
#include <time.h>  
#include "iodos.h" 
#define antall_farger 6 //Spillet kræsjer med mindre enn 4 farger.
#define maks_antall_omganger 10 //antall forsøk spilleren har.
#define false 0
#define true 1 

using namespace std; 
 

/*Prototype deklarasjoner*/
void random_a(int datans_kode[4]); 
void random_b(int datans_kode[4]);
void outro (int datans_kode[4]);

//-----------------------------------------------------------------------------
/*
FUNKSJONENS NAVN:	intro
HENSIKT:	
	Gir kort introduksjon til spillet, og gir spilleren valget mellom å spille 
	den forenklede eller vanlige versjonen. Respektive psudo random kode blir
	så generert og verdiene blir puttet i et array.

PARAMETRE:
navn:			type:		deskripsjon:
--------------------------------------------------------------------------
datans_kode		int			array som holder den hemmelige koden i spillet

KALLER OPP:	random_a, random_b

KALLES FRA: mastermind
	
*/

void intro(int datans_kode[4])
{
	char version;

	system ("CLS");
	cout <<"\tVelkommen til Mastermind !\n\n";
	cout <<"\tSpillet går ut på å gjette de fire pinnenes farge og sekvens.\n";
	cout <<"\tFargene er represenert av tall mellom 1 og " <<antall_farger <<".\n";
	cout <<"\tI forenklet versjon gjetter du på fire forskjellige tall.\n";
	cout <<"\tMens i vanlig versjon kan det være flere av det samme tallet.\n\n";
	cout <<"\tSvart pinne betyr at du har rett farge på riktig plass.\n";
	cout <<"\tHvit pinne betyr at du har rett farge men på feil plass.\n\n";
	cout <<"\tVil du spille forenklet eller vanlig version ? \n";
	cout <<"\tTast F eller V etterfulgt av <enter> :";
	cin >>version;
	
	if (version=='f' || version=='F')
		{
		cout <<"\n\tDu har valgt å spille den forenklede versionen.\n\n";
		random_a(datans_kode); //datans_kode får 4 unike tall i sub funksjonen.
		}
	else
		{
		cout <<"\n\tDu har valgt å spille den vanlige versjonen.\n\n";
		random_b(datans_kode); //datans_kode får 4 tall (ei unike) i sub funksjonen.  
		}
	


}

//-----------------------------------------------------------------------------
/*
FUNKSJONENS NAVN:	random_a
HENSIKT:	
	Å genere fire forskjellige tall med psudo random og putte tallene i et 
	array som holder koden det skal gjettes på.

PARAMETRE:
navn:			type:		deskripsjon:
--------------------------------------------------------------------------
datans_kode		int			array som holder den hemmelige koden i spillet	

KALLER OPP:	ingen

KALLES FRA: intro
	
*/

void random_a(int datans_kode[4])
{
	srand (time (NULL) );/*pseudo-random fra klokken til systemet (random seed):  */
	datans_kode[0] = rand()%antall_farger+1; /* Her legges det første tallet i arrayet*/
	
/* Her legges det andre tallet i arrayet og 
   gjentas hvis tallet er det samme som det første: */
	do	{
		datans_kode[1] = rand()%antall_farger+1;
		}
	while (datans_kode[1]==0 || datans_kode[1]==datans_kode[0]);

/* Her legges det tredje tallet i arrayet og 
   gjentas hvis tallet er det samme som noen av de andre */	
		do 
		{
		datans_kode[2] = rand()%antall_farger+1;
		}
	while (datans_kode[2]==0
		|| datans_kode[2]==datans_kode[1]
	    || datans_kode[2]==datans_kode[0] );
	
/* Her legges det fjerde tallet i arrayet og 
   gjentas hvis tallet er det samme som noen av de andre */		
	do
		{
		datans_kode[3] = rand()%antall_farger+1;
		}
	while (datans_kode[3]==0 
	|| datans_kode[3]==datans_kode[2] 
	|| datans_kode[3]==datans_kode[1] 
	|| datans_kode[3]==datans_kode[0]);
	
}

//-----------------------------------------------------------------------------
/*
FUNKSJONENS NAVN:	random_a
HENSIKT:	
	Å genere fire tall (ikke nødvendigvis unike) med psudo random og putte 
	tallene i et array som holder koden det skal gjettes på. (Det kan bli
	flere av samme tall)

PARAMETRE:
navn:			type:		deskripsjon:
--------------------------------------------------------------------------
datans_kode		int			array som holder den hemmelige koden i spillet	

KALLER OPP:	ingen

KALLES FRA: intro

*/

void random_b(int datans_kode[4])
{
	srand (time (NULL) );
	datans_kode[0] = rand()%antall_farger+1;
	datans_kode[1] = rand()%antall_farger+1;
	datans_kode[2] = rand()%antall_farger+1;
	datans_kode[3] = rand()%antall_farger+1;

}

//-----------------------------------------------------------------------------
/*
FUNKSJONENS NAVN:	inntasting
HENSIKT:	
	Denne funksjonen vil ta imot inntasting fra spilleren.
	De fire sifrede tallet blir omgjordt til fire tall som så blir lagret 
	på hver sin respektive plassering i et array.

PARAMETRE:
navn:				type:		deskripsjon:
--------------------------------------------------------------------------
spillerens_kode		int			array som holder spillerens kode	

KALLER OPP:	ingen

KALLES FRA: mastermind

*/

void inntasting(int spillerens_kode[4])
{
	int inntasting_av_kode; 
	cout <<"\n\tGjett 4 tall mellom 1 og " <<antall_farger <<": ";
	cin >>inntasting_av_kode;

     spillerens_kode[0]=int(inntasting_av_kode/1000); 
     spillerens_kode[1]=(int(inntasting_av_kode/100))-spillerens_kode[0]*10;
     spillerens_kode[3]=inntasting_av_kode%10;
	 spillerens_kode[2]=((inntasting_av_kode%100)-spillerens_kode[3])/10;

}
//-----------------------------------------------------------------------------
/*
FUNKSJONENS NAVN:	feilmelding
HENSIKT:	
	Denne funksjonen tar imot spillerens_kode og ser om inntastingen er gyldig
	heller ikke. (Dvs. at tallene er 4 stk og mellom 1 og antall farger.)

PARAMETRE:
navn:				type:		deskripsjon:
--------------------------------------------------------------------------
spillerens_kode		int			array som holder spillerens kode	

KALLER OPP:	ingen

KALLES FRA: mastermind

*/

int feilmelding (int spillerens_kode[4])
{

	if (spillerens_kode[0]<=0 || spillerens_kode[0]>antall_farger)
		{
		cout <<"\tDu tastet feil.\n\tVennligst tast et tall mellom 1 og ";
		cout <<antall_farger <<"\n\tForsøket telles ikke.\n";
		return false;
		}
	else if(spillerens_kode[1]<=0 || spillerens_kode[1]>antall_farger)
		{
		cout <<"\tDu tastet feil.\n\tVennligst tast et tall mellom 1 og ";
		cout <<antall_farger <<"\n\tForsøket telles ikke.\n";
		return false;
		}
	
	else if(spillerens_kode[2]<=0 || spillerens_kode[2]>antall_farger)
		{
		cout <<"\tDu tastet feil.\n\tVennligst tast et tall mellom 1 og ";
		cout <<antall_farger <<"\n\tForsøket telles ikke.\n";
		return false;
		}
	
	else if(spillerens_kode[3]<=0 || spillerens_kode[3]>antall_farger)
		{
		cout <<"\tDu tastet feil.\n\tVennligst tast et tall mellom 1 og ";
		cout <<antall_farger <<"\n\tForsøket telles ikke.\n";
		return false;
		}

	else return true;

	/*Dette trodde jeg også kunne skrives slik som nedenfor, men det ble funnet feil ved testing.
      Kodeeksemplet detekterer ikke om bare ett av det andre, tredje eller fjerde tallet er 
	  høyere enn antall_farger. (Jeg vet ikke hvorfor.)
 
 for (int i=0; i<4; i++)
	{
	 if (spillerens_kode[0]<=0 || spillerens_kode[0]>antall_farger)
		{
		cout <<"\tDu tastet feil. Vennligst tast et tall mellom 1 og " <<antall_farger <<"\n";
		return false;
		break;
		}
	}*/


}

//-----------------------------------------------------------------------------
/*
FUNKSJONENS NAVN:	svart_pinne
HENSIKT:	
	Denne funksjonen teller antall svarte pinner (riktig farge på riktig plass).
	Variabelen telle_plassering sørger for at når en plassering i datans_kode 
	har blitt funnet lik spillerens inntastede kode som enten svart eller hvit 
	pinne kan den ikke telles igjen.

PARAMETRE:
navn:				type:		deskripsjon:
--------------------------------------------------------------------------
spillerens_kode		int			array som holder spillerens kode	
datans_kode			int			array som holder den hemmelige koden
telle_plassering	int			array som holder plasseringen til en pinne

KALLER OPP:	ingen

KALLES FRA: mastermind
 */

void svart_pinne(int spillerens_kode[4], int datans_kode[4], int telle_plassering[4])
{
	int antall_svarte_pinner=0;

	for (int i=0; i<4; i++) telle_plassering[i]=false; //nullstilling

	for (int i=0; i<4; i++)
	{
		if (spillerens_kode[i]==datans_kode[i])
		{
		antall_svarte_pinner++;
		telle_plassering[i]=true;
		}
	}
	
	cout <<"\tDu har " <<antall_svarte_pinner <<" stk svarte pinner.\n";

}

//-----------------------------------------------------------------------------
/*
FUNKSJONENS NAVN:	hvit_pinne
HENSIKT:	
	Denne funksjonen teller antall hvite pinner (riktig farge på feil plass).
	Den finner altså om om de to innkommende argumentene spillerens_kode og 
	datas_kode inneholder samme tall men på en annen plassering i arrayet.

PARAMETRE:
navn:				type:		deskripsjon:
--------------------------------------------------------------------------
spillerens_kode		int			array som holder spillerens kode	
datans_kode			int			array som holder den hemmelige koden
telle_plassering	int			array som holder plasseringen til en pinne

KALLER OPP:	ingen

KALLES FRA: mastermind
*/

void hvit_pinne(int spillerens_kode[4], int datans_kode[4], int telle_plassering[4])
{
	int antall_hvite_pinner=0;

	for (int i=0; i<5; i++)
	{
		for (int j=0; j<5; j++)
		{
			if ((spillerens_kode[i]==datans_kode[j]) && telle_plassering[j]==false)
				{
				antall_hvite_pinner++;
				telle_plassering[j]=true;
				}
		}
	}
	
	cout <<"\tDu har " <<antall_hvite_pinner <<" stk hvite pinner.\n";
}

//-----------------------------------------------------------------------------
/*
FUNKSJONENS NAVN:	mastermind
HENSIKT:
	Denne funksjonen er selve "hendelse-forløpet" til spillet som er i en do
	while lopp. Her kalles alle de andre funksjonene i spillet opp i riktig 
	rekkefølge. Og det avgjøres om den hemmelige koden er lik den inntastede
	koden. Antall omganger telles også og loopen avbrytes hvis maks antall
	omganger er nådd.


PARAMETRE:
navn:				type:		deskripsjon:
--------------------------------------------------------------------------
ingen

KALLER OPP:	intro, inntasting, feilmelding, svart_pinne, hvit_pinne, outro

KALLES FRA: meny
*/

int mastermind()
{
	int spillerens_kode[4], datans_kode[4], telle_plassering[4], antall_omganger=0;
	
	intro(datans_kode);
	
	do
	{
		do
		{
		inntasting(spillerens_kode);
		}
		while(feilmelding(spillerens_kode)==false);

		antall_omganger++;
		cout <<"\tOmgang nr. " <<antall_omganger <<endl;;
		svart_pinne(spillerens_kode, datans_kode, telle_plassering);
		hvit_pinne(spillerens_kode, datans_kode, telle_plassering);

		if (datans_kode[0]==spillerens_kode[0] && datans_kode[1]==spillerens_kode[1] && datans_kode[2]==spillerens_kode[2] && datans_kode[3]==spillerens_kode[3])
		{	
		cout <<"\n\tGratulerer du klarte det på " <<antall_omganger <<" forsøk\n";
		break;
		}

		else if (antall_omganger==maks_antall_omganger)
		{
		cout <<"\tDesverre, du klarte det ikke på forsøk nr." <<antall_omganger <<endl;
		cout <<"\tRikig svar var: ";
		for (int i=0; i<4; i++) cout <<datans_kode[i];
		cout <<endl;
		break;
		}

		/*Disse linjene kan aktivers for å teste programmet:*/ 
		cout <<"\tDatans kode:    "<<datans_kode[0] <<datans_kode[1] <<datans_kode[2] <<datans_kode[3] <<endl; //forhåndsvisning
		cout <<"\tSpilleren kode:"<<spillerens_kode[0] <<spillerens_kode[1] <<spillerens_kode[2] <<spillerens_kode[3] <<endl;
	
	}while (datans_kode[0]!=spillerens_kode[0] || datans_kode[1]!=spillerens_kode[1] || datans_kode[2]!=spillerens_kode[2] || datans_kode[3]!=spillerens_kode[3]);
		
	outro(datans_kode);
	return antall_omganger;
}

//-----------------------------------------------------------------------------
/*
FUNKSJONENS NAVN:	outro
HENSIKT:
	I denne funksjonen velges det om spillet skal spilles pånytt eller ikke.
	Hvis spilleren velger ja så nullstilles datans kode før mastermind
	kalles opp fra begynnelsen, ellers avsluttes spillet.

PARAMETRE:
navn:				type:		deskripsjon:
--------------------------------------------------------------------------
datans_kode			int			array som holder den hemmelige koden

KALLER OPP:	mastermind

KALLES FRA: mastermind
*/

void outro (int datans_kode[4])
{
char ja_nei;

cout <<"\tVil du spille igjen (j/n) ? ";
cin >>ja_nei;

if (ja_nei=='j' || ja_nei=='J')
	{
	for (int i=0; i<4; i++) datans_kode[i]=0;

	mastermind();
	}
else
	{
	cout <<"\tHadet bra ! Velkommen tilbake.\n";
	}

}

//-----------------------------------------------------------------------------
/*
FUNKSJONENS NAVN:	menyvalg
HENSIKT:
	Denne funksjonen er et switch sats som kan brukes istedet for if der man
	har flere valg situasjoner.

PARAMETRE:
navn:				type:		deskripsjon:
--------------------------------------------------------------------------
meny				int			innholder menyvalget

KALLER OPP:	mastermind

KALLES FRA: meny  
*/

void menyvalg(int meny)
	{
	switch (meny){
	default:break;
	case 1: mastermind();break;
	}
}

//-----------------------------------------------------------------------------
/*
FUNKSJONENS NAVN:	meny
HENSIKT:
	Denne funksjonen viser menyen på skjermen og tar imot valget (inntastingen) 
	fra brukeren.

PARAMETRE:
navn:				type:		deskripsjon:
--------------------------------------------------------------------------
meny				int			innholder menyvalget

KALLER OPP:	menuvalg

KALLES FRA: main
*/

void meny()
{
	int meny;
	do
	{
	system ("cls");
	cout <<"\n\t   Velg fra menyen:\n";
	cout <<"\n\t1.  Mastermind.\n";
	cout <<"\n\t2.  Avslutte applikasjonen.\n\n";
	cin  >> meny;
	cin.ignore(80,'\n'); 
	menyvalg(meny);
	}
	while(meny!=2);
	cout <<"\n\t";
}


//-----------------------------------------------------------------------------

int main()
{
	dos_console(); //støtte for øæå
	meny();
	
	return 0;
}

//-----------------------------------------------------------------------------



