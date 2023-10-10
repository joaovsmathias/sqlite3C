#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Ssu_protocol{

	char *id;
    char *timestamp;
    char *demanda_fim;
    char *pulsos_ept;
    char *pulsos_epr;
    char *posto;
    char *posto_tarifario;
    char *tarifa_reativo;
    char *reposicao_demanda;
    char *intervalo_reativo;
    char *pulsos_capacitivos;
    char *pulsos_indutivos;
    char *ept;

};
struct Default_protocol{
    char *id;
    char *timestamp;
    char *sn;
    char *posto;
    char *saida_usr;
    char *van;
    char *vbn;
    char *vcn;
    char *ia;
    char *ib;
    char *ic;
    char *pa;
    char *pb;
    char *pc;
    char *pt;
    char *qa;
    char *qb;
    char *qc;
    char *qt;
    char *sa;
    char *sb;
    char *sc;
    char *st;
    char *phiab;
    char *phibc;
    char *phica;
    char *cosphia;
    char *cosphib;
    char *cosphic;
    char *freq;
    char *fpa;
    char *fpb;
    char *fpc;
    char *fp;
    char *ept;
    char *ep1;
    char *ep2;
    char *ep3;
};

struct Record {
    int id;
    char content[1500]; 
    char datetime[20]; 
};


sqlite3 *db;
char *err_msg = 0;
int rc;
int first_id;
int last_id;
struct Record dado;
struct Ssu_protocol ssu_dados;
struct Default_protocol default_dados;
int has_next;


char *encode_ssu(struct Ssu_protocol dados) {
    char encode_ssud_string[600]; 
    
     snprintf(encode_ssud_string, sizeof(encode_ssud_string), "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s",
             dados.id, dados.timestamp, dados.demanda_fim, dados.pulsos_ept, dados.pulsos_epr,
             dados.posto, dados.posto_tarifario, dados.tarifa_reativo, dados.reposicao_demanda,
             dados.intervalo_reativo, dados.pulsos_capacitivos, dados.pulsos_indutivos, dados.ept);

    
    char *result = strdup(encode_ssud_string);
    return result;
}


struct Ssu_protocol decode_ssu(const char *encode_ssud_string) {
    struct Ssu_protocol dados;
    

    // Usar strtok para dividir a string em campos usando o caractere '|' como delimitador
    char *token = strtok((char *)encode_ssud_string, "|");
    dados.id = strdup(token);
    
    token = strtok(NULL, "|");
    dados.timestamp = strdup(token);
    
    
    token = strtok(NULL, "|");
    dados.demanda_fim = strdup(token);
    token = strtok(NULL, "|");
    dados.pulsos_ept = strdup(token);
    token = strtok(NULL, "|");
    dados.pulsos_epr = strdup(token);
    token = strtok(NULL, "|");
    dados.posto = strdup(token);
    token = strtok(NULL, "|");
    dados.posto_tarifario = strdup(token);
    token = strtok(NULL, "|");
    dados.tarifa_reativo = strdup(token);
    token = strtok(NULL, "|");
    dados.reposicao_demanda = strdup(token);
    token = strtok(NULL, "|");
    dados.intervalo_reativo = strdup(token);
    token = strtok(NULL, "|");
    dados.pulsos_capacitivos = strdup(token);
    token = strtok(NULL, "|");
    dados.pulsos_indutivos = strdup(token);
    token = strtok(NULL, "|");
    dados.ept = strdup(token);
   
    

    return dados;
}


char *encode_default(struct Default_protocol dados) {
    char encode_default_string[1000]; 
    
     snprintf(encode_default_string, sizeof(encode_default_string), "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s",
             dados.id, dados.timestamp, dados.sn, dados.posto, dados.saida_usr, dados.van, dados.vbn, dados.vcn, dados.ia,
             dados.ib, dados.ic, dados.pa, dados.pb, dados.pc, dados.pt, dados.qa, dados.qb, dados.qc, dados.qt, dados.sa, dados.sb, 
             dados.sc, dados.st, dados.phiab, dados.phibc, dados.phica, dados.cosphia, dados.cosphib, dados.cosphic, dados.freq, 
             dados.fpa, dados.fpb, dados.fpc, dados.fp, dados.ept, dados.ep1, dados.ep2, dados.ep3);

    
    char *result = strdup(encode_default_string);
    return result;
}

struct Default_protocol decode_default(const char *encode_default_string) {
    struct Default_protocol dados;
    

    
    char *token = strtok((char *)encode_default_string, "|");
    dados.id = strdup(token);
    token = strtok(NULL, "|");
    dados.timestamp = strdup(token);
    token = strtok(NULL, "|");
    dados.sn = strdup(token);
    token = strtok(NULL, "|");
    dados.posto = strdup(token);
    token = strtok(NULL, "|");
    dados.saida_usr = strdup(token);
    token = strtok(NULL, "|");
    dados.van = strdup(token);
    token = strtok(NULL, "|");
    dados.vbn = strdup(token);
    token = strtok(NULL, "|");
    dados.vcn = strdup(token);
    token = strtok(NULL, "|");
    dados.ia = strdup(token);
    token = strtok(NULL, "|");
    dados.ib = strdup(token);
    token = strtok(NULL, "|");
    dados.ic = strdup(token);
    token = strtok(NULL, "|");
    dados.pa = strdup(token);
    token = strtok(NULL, "|");
    dados.pb = strdup(token);
    token = strtok(NULL, "|");
    dados.pc = strdup(token);
    token = strtok(NULL, "|");
    dados.pt = strdup(token);
    token = strtok(NULL, "|");
    dados.qa = strdup(token);
    token = strtok(NULL, "|");
    dados.qb = strdup(token);
    token = strtok(NULL, "|");
    dados.qc = strdup(token);
    token = strtok(NULL, "|");
    dados.qt = strdup(token);
    token = strtok(NULL, "|");
    dados.sa = strdup(token);
    token = strtok(NULL, "|");
    dados.sb = strdup(token);
    token = strtok(NULL, "|");
    dados.sc = strdup(token);
    token = strtok(NULL, "|");
    dados.st = strdup(token);
    token = strtok(NULL, "|");
    dados.phiab = strdup(token);
    token = strtok(NULL, "|");
    dados.phibc = strdup(token);
    token = strtok(NULL, "|");
    dados.phica = strdup(token);
    token = strtok(NULL, "|");
    dados.cosphia = strdup(token);
    token = strtok(NULL, "|");
    dados.cosphib = strdup(token);
    token = strtok(NULL, "|");
    dados.cosphic = strdup(token);
    token = strtok(NULL, "|");
    dados.freq = strdup(token);
    token = strtok(NULL, "|");
    dados.fpa = strdup(token);
    token = strtok(NULL, "|");
    dados.fpb = strdup(token);
    token = strtok(NULL, "|");
    dados.fpc = strdup(token);
    token = strtok(NULL, "|");
    dados.fp = strdup(token);
    token = strtok(NULL, "|");
    dados.ept = strdup(token);
    token = strtok(NULL, "|");
    dados.ep1 = strdup(token);
    token = strtok(NULL, "|");
    dados.ep2 = strdup(token);
    token = strtok(NULL, "|");
    dados.ep3 = strdup(token);
    

    return dados;
}



int create_sqlite_connection(void){
    
    rc = sqlite3_open("offline.db", &db);
    

    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }

    
    char *sql = "CREATE TABLE IF NOT EXISTS Offline_Storage(Id INTEGER PRIMARY KEY AUTOINCREMENT, Data TEXT, Datetime DATETIME);" ;

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    }

    return 0;
}

int insert_sqlite_data(){


    /*
    char sql[600];
    char *encode_ssud_string = encode_ssu(ssu_dados);
    strcpy(dado.content, encode_ssud_string);*/

    char sql[1000];
    char *encode_default_string = encode_default(default_dados);
    
    strcpy(dado.content, encode_default_string);


    sprintf(sql, "INSERT INTO Offline_Storage (Data,Datetime) VALUES('%s', datetime('now'));", dado.content);
    
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    } 
}

int callback_first_id(void *NotUsed, int argc, char **argv, 
                    char **azColName) {
    
    NotUsed = 0;
    first_id = atoi(argv[0]);
    //printf("%d\n",first_id);
    return 0;
}

int callback_last_id(void *NotUsed, int argc, char **argv, 
                    char **azColName) {
    
    NotUsed = 0;
    last_id = atoi(argv[0]);
    //printf("%d\n",first_id);
    return 0;
}

int find_id_callback(void *NotUsed, int argc, char **argv, 
                    char **azColName) {
    
    NotUsed = 0;
    
    dado.id = atoi(argv[0]);
    snprintf(dado.content, sizeof(dado.content), argv[1]);
    snprintf(dado.datetime, sizeof(dado.datetime), argv[2]); 

    
    return 0;
}

int callback_has_next(void *NotUsed, int argc, char **argv, 
                    char **azColName) {
    
    NotUsed = 0;
    
    //printf("%d\n",atoi(argv[0]));
    if(atoi(argv[0])>0){
        has_next=1;
        return 0;
    }
    
    has_next=0;
    return 0;
}

int get_last_id_sqlite(void){
    char *sql = "SELECT * FROM Offline_Storage order by Id DESC limit 1";
        
    rc = sqlite3_exec(db, sql, callback_last_id, 0, &err_msg);
}




int get_first_id_sqlite(void){

    char *sql = "SELECT * FROM Offline_Storage order by Id ASC limit 1";
        
    rc = sqlite3_exec(db, sql, callback_first_id, 0, &err_msg);
}


int delete_value_by_id(int id){
    
    char sql[100];
    sprintf(sql, "DELETE FROM Offline_Storage WHERE Id=%d", id);
    
        
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

}

int get_value_by_id(int id){
    char sql[100];
    sprintf(sql, "SELECT * FROM Offline_Storage WHERE Id=%d", id);
    
        
    rc = sqlite3_exec(db, sql, find_id_callback, 0, &err_msg);
}

int has_next_record(void){
    char *sql = "SELECT count(*) FROM Offline_Storage";
        
    rc = sqlite3_exec(db, sql, callback_has_next, 0, &err_msg);
}

void popula_SSU(void){
    ssu_dados.id = strdup("abnt14522_ssu");
    ssu_dados.timestamp = strdup("2023-10-09 14:18:58");
    ssu_dados.demanda_fim = strdup("0");
    ssu_dados.pulsos_ept = strdup("917");
    ssu_dados.pulsos_epr = strdup("57");
    ssu_dados.posto = strdup("FORA PONTA");
    ssu_dados.posto_tarifario = strdup("AZUL");
    ssu_dados.tarifa_reativo = strdup("SIM");
    ssu_dados.reposicao_demanda = strdup("0");
    ssu_dados.intervalo_reativo = strdup("0");
    ssu_dados.pulsos_capacitivos = strdup("SIM");
    ssu_dados.pulsos_indutivos = strdup("NAO");
    ssu_dados.ept = strdup("0.28");
}


void popula_Default(void){
    default_dados.id= strdup("abnt14522");
    default_dados.timestamp= strdup("2023-10-09 10:45:54");
    default_dados.sn= strdup("0000004197");
    default_dados.posto= strdup("0000000000");
    default_dados.saida_usr= strdup("0000000001");
    default_dados.van= strdup("0.00");
    default_dados.vbn= strdup("122.24");
    default_dados.vcn= strdup("122.07");
    default_dados.ia= strdup("0.00");
    default_dados.ib= strdup("11.93");
    default_dados.ic= strdup("1.74");
    default_dados.pa= strdup("0.00");
    default_dados.pb= strdup("1031.25");
    default_dados.pc= strdup("194.53");
    default_dados.pt= strdup("1225.78");
    default_dados.qa= strdup("0.00");
    default_dados.qb= strdup("1031.02");
    default_dados.qc= strdup("84.72");
    default_dados.qt= strdup("1115.74");
    default_dados.sa= strdup("0.00");
    default_dados.sb= strdup("1458.25");
    default_dados.sc= strdup("212.18");
    default_dados.st= strdup("1657.53");
    default_dados.phiab= strdup("0.00");
    default_dados.phibc= strdup("0.00");
    default_dados.phica= strdup("0.00");
    default_dados.cosphia= strdup("-nan");
    default_dados.cosphib= strdup("-nan");
    default_dados.cosphic= strdup("-nan");
    default_dados.freq= strdup("0.00");
    default_dados.fpa= strdup("51186992.00");
    default_dados.fpb= strdup("0.00");
    default_dados.fpc= strdup("0.70");
    default_dados.fp= strdup("0.91");
    default_dados.ept= strdup("4971.80");
    default_dados.ep1= strdup("99.56");
    default_dados.ep2= strdup("4872.00");
    default_dados.ep3= strdup("0.24");
}


void printSSU(struct Ssu_protocol ssu_dados) {
    printf("ID: %s\n", ssu_dados.id);
    printf("Timestamp: %s\n", ssu_dados.timestamp);
    printf("Demanda Fim: %s\n", ssu_dados.demanda_fim);
    printf("Pulsos EPT: %s\n", ssu_dados.pulsos_ept);
    printf("Pulsos EPR: %s\n", ssu_dados.pulsos_epr);
    printf("Posto: %s\n", ssu_dados.posto);
    printf("Posto Tarifário: %s\n", ssu_dados.posto_tarifario);
    printf("Tarifa Reativo: %s\n", ssu_dados.tarifa_reativo);
    printf("Reposição Demanda: %s\n", ssu_dados.reposicao_demanda);
    printf("Intervalo Reativo: %s\n", ssu_dados.intervalo_reativo);
    printf("Pulsos Capacitivos: %s\n", ssu_dados.pulsos_capacitivos);
    printf("Pulsos Indutivos: %s\n", ssu_dados.pulsos_indutivos);
    printf("EPT: %s\n", ssu_dados.ept);
}

void printDefault(struct Default_protocol default_dados) {
    printf("ID: %s\n", default_dados.id);
    printf("Timestamp: %s\n", default_dados.timestamp);
    printf("SN: %s\n", default_dados.sn);
    printf("Posto: %s\n", default_dados.posto);
    printf("Saída Usuário: %s\n", default_dados.saida_usr);
    printf("Van: %s\n", default_dados.van);
    printf("Vbn: %s\n", default_dados.vbn);
    printf("Vcn: %s\n", default_dados.vcn);
    printf("Ia: %s\n", default_dados.ia);
    printf("Ib: %s\n", default_dados.ib);
    printf("Ic: %s\n", default_dados.ic);
    printf("Pa: %s\n", default_dados.pa);
    printf("Pb: %s\n", default_dados.pb);
    printf("Pc: %s\n", default_dados.pc);
    printf("Pt: %s\n", default_dados.pt);
    printf("Qa: %s\n", default_dados.qa);
    printf("Qb: %s\n", default_dados.qb);
    printf("Qc: %s\n", default_dados.qc);
    printf("Qt: %s\n", default_dados.qt);
    printf("Sa: %s\n", default_dados.sa);
    printf("Sb: %s\n", default_dados.sb);
    printf("Sc: %s\n", default_dados.sc);
    printf("St: %s\n", default_dados.st);
    printf("Phiab: %s\n", default_dados.phiab);
    printf("Phibc: %s\n", default_dados.phibc);
    printf("Phica: %s\n", default_dados.phica);
    printf("Cosphia: %s\n", default_dados.cosphia);
    printf("Cosphib: %s\n", default_dados.cosphib);
    printf("Cosphic: %s\n", default_dados.cosphic);
    printf("Freq: %s\n", default_dados.freq);
    printf("Fpa: %s\n", default_dados.fpa);
    printf("Fpb: %s\n", default_dados.fpb);
    printf("Fpc: %s\n", default_dados.fpc);
    printf("FP: %s\n", default_dados.fp);
    printf("Ept: %s\n", default_dados.ept);
    printf("Ep1: %s\n", default_dados.ep1);
    printf("Ep2: %s\n", default_dados.ep2);
    printf("Ep3: %s\n", default_dados.ep3);
}


int main(void) {
    
    create_sqlite_connection();
    //get_first_id_sqlite();
    //get_last_id_sqlite();
    //printf("First ID ==>%d\n",first_id);
    //printf("Last ID ==>%d\n",last_id);
    //delete_value_by_id(first_id);
    
    
    
    
    
    get_value_by_id(1);
    //printf("\n%s\n",dado.content);
    //popula_SSU();
    
    //ssu_dados = decode_ssu(dado.content);
    default_dados = decode_default(dado.content);
    //printSSU(ssu_dados);
    //has_next_record();
    //printf("%d",has_next);
    //popula_Default();
    printDefault(default_dados);
    //insert_sqlite_data();

    sqlite3_close(db);

    return 0;
}