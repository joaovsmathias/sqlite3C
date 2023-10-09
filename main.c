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

struct Record {
    int id;
    char content[800]; 
    char datetime[20]; 
};


sqlite3 *db;
char *err_msg = 0;
int rc;
int first_id;
struct Record dado;
struct Ssu_protocol ssu_dados;


char *encode(struct Ssu_protocol dados) {
    char encoded_string[600]; 
    
     snprintf(encoded_string, sizeof(encoded_string), "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s",
             dados.id, dados.timestamp, dados.demanda_fim, dados.pulsos_ept, dados.pulsos_epr,
             dados.posto, dados.posto_tarifario, dados.tarifa_reativo, dados.reposicao_demanda,
             dados.intervalo_reativo, dados.pulsos_capacitivos, dados.pulsos_indutivos, dados.ept);

    
    char *result = strdup(encoded_string);
    return result;
}


struct Ssu_protocol decode(const char *encoded_string) {
    struct Ssu_protocol dados;

    // Usar strtok para dividir a string em campos usando o caractere '|' como delimitador
    char *token = strtok((char *)encoded_string, "|");
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


    
    char sql[600];
    char *encoded_string = encode(ssu_dados);
    
    strcpy(dado.content, encoded_string);
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
    printf("%d\n",first_id);
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

int get_last_id_sqlite(void){
    int last_id = sqlite3_last_insert_rowid(db);
    return last_id;
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

int main(void) {
    
    create_sqlite_connection();
    //get_first_id_sqlite();
    //delete_value_by_id(first_id);
    get_value_by_id(1);
    //popula_SSU();
    //insert_sqlite_data();
    ssu_dados = decode(dado.content);
    printSSU(ssu_dados);

    sqlite3_close(db);

    return 0;
}