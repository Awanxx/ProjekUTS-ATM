#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Transaction {
    char operation[50];
    struct Transaction *next;
};


struct Transaction *history = NULL;

void addToHistory(char *operation) {
    struct Transaction *newNode = (struct Transaction *)malloc(sizeof(struct Transaction));
    strcpy(newNode->operation, operation);
    newNode->next = history;
    history = newNode;
}

void displayHistory() {
    printf("\n=== Riwayat Transaksi ===\n");
    struct Transaction *temp = history;
    while (temp != NULL) {
        printf("%s\n", temp->operation);
        temp = temp->next;
    }
}


void saveTransactionHistoryToFile() {
    FILE *file = fopen("transaksi.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk disimpan.\n");
        return;
    }

    struct Transaction *temp = history;
    while (temp != NULL) {
        fprintf(file, "%s\n", temp->operation);
        temp = temp->next;
    }

    fclose(file);
}

#define MAX_SIZE 100

struct Stack {
    char operation[MAX_SIZE][50];
    int top;
};

void initializeStack(struct Stack *stack) {
    stack->top = -1;
}

void push(struct Stack *stack, char *operation) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack penuh.\n");
        return;
    }
    strcpy(stack->operation[++stack->top], operation);
}

void pop(struct Stack *stack) {
    if (stack->top == -1) {
        printf("Stack kosong.\n");
        return;
    }
    printf("Transaksi terhapus: %s\n", stack->operation[stack->top--]);
}

struct QueueNode {
    char operation[50];
    struct QueueNode *next;
};

struct Queue {
    struct QueueNode *front, *rear;
};

void initializeQueue(struct Queue *queue) {
    queue->front = queue->rear = NULL;
}

void enqueue(struct Queue *queue, char *operation) {
    struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    strcpy(newNode->operation, operation);
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

void dequeue(struct Queue *queue) {
    if (queue->front == NULL) {
        printf("Queue kosong.\n");
        return;
    }
    struct QueueNode *temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
}

void displayMenu() {
    printf("\n+------- Warkop Central Asia -------+\n");
    printf("| No |            Menu              |\n");
    printf("|----|------------------------------|\n");
    printf("|  1 |Info Saldo                    |\n");
    printf("|  2 |Setor Tunai                   |\n");
    printf("|  3 |Tarik Tunai                   |\n");
    printf("|  4 |Transfer Antar Rekening       |\n");
    printf("|  5 |Transfer Antar Bank           |\n");
    printf("|  6 |Top-up Flazz                  |\n");
    printf("|  7 |Bayar Tagihan Listrik         |\n");
    printf("|  8 |Pembayaran Tiket dan Hotel    |\n");
    printf("|  9 |Pembelian Pulsa               |\n");
    printf("| 10 |Lihat Riwayat Transaksi       |\n");
    printf("| 11 |Scan QRIS                     |\n");
    printf("| 12 |Keluar                        |\n");
    printf("+-----------------------------------+\n");
}

void checkBalance(float saldo) {
    printf("Saldo Anda: Rp%.2f\n", saldo);
}

float deposit(float saldo) {
    float jumlah;
    printf("Masukkan jumlah yang ingin disetor: Rp");
    if (scanf("%f", &jumlah) != 1 || jumlah < 0) {
        printf("Input tidak valid. Harap masukkan angka yang valid.\n");
        while (getchar() != '\n');
        return saldo;
    }
    saldo += jumlah;
    char operation[50];
    sprintf(operation, "Setor Tunai: Rp%.2f", jumlah);
    addToHistory(operation);
    printf("Setor tunai berhasil.\n");
    return saldo;
}

float withdraw(float saldo) {
    float jumlah;
    printf("Masukkan jumlah yang ingin ditarik: Rp");
    if (scanf("%f", &jumlah) != 1 || jumlah < 0) {
        printf("Input tidak valid. Harap masukkan angka yang valid.\n");
        while (getchar() != '\n');
        return saldo;
    }
    if (jumlah > saldo) {
        printf("Saldo tidak mencukupi.\n");
    } else {
        saldo -= jumlah;
        char operation[50];
        sprintf(operation, "Tarik Tunai: Rp%.2f", jumlah);
        addToHistory(operation);
        printf("Tarik tunai berhasil.\n");
    }
    return saldo;
}

void transfer(float *saldopengirim, float *saldo_penerima) {
    float jumlah;
    printf("Masukkan jumlah yang ingin ditransfer: Rp");
    if (scanf("%f", &jumlah) != 1 || jumlah < 0) {
        printf("Input tidak valid. Harap masukkan angka yang valid.\n");
        while (getchar() != '\n');
        return;
    }
    if (jumlah > *saldopengirim) {
        printf("Saldo tidak mencukupi.\n");
    } else {
        *saldopengirim -= jumlah;
        *saldo_penerima += jumlah; 
        char operation[50];
        sprintf(operation, "Transfer: Rp%.2f", jumlah);
        addToHistory(operation);
        printf("Transfer berhasil.\n");
    }
}


float topUpFlazz(float saldo) {
    float jumlah;
    printf("Masukkan jumlah top-up Flazz: Rp");
    if (scanf("%f", &jumlah) != 1 || jumlah < 0) {
        printf("Input tidak valid. Harap masukkan angka yang valid.\n");
        while (getchar() != '\n');
        return saldo;
    }
    if (jumlah > saldo) {
        printf("Saldo tidak mencukupi untuk top-up Flazz.\n");
    } else {
        saldo -= jumlah;
        char operation[50];
        sprintf(operation, "Top-up Flazz: Rp%.2f", jumlah);
        addToHistory(operation);
        printf("Top-up Flazz berhasil.\n");
    }
    return saldo; 
}

float bayarTagihanListrik(float saldo) {
    float jumlah_tagihan;
    printf("Masukkan jumlah tagihan listrik: Rp");
    if (scanf("%f", &jumlah_tagihan) != 1 || jumlah_tagihan < 0) {
        printf("Input tidak valid. Harap masukkan angka yang valid.\n");
        while (getchar() != '\n');
        return saldo;
    }
    if (jumlah_tagihan > saldo) {
        printf("Saldo tidak mencukupi untuk membayar tagihan listrik.\n");
    } else {
        saldo -= jumlah_tagihan;
        char operation[50];
        sprintf(operation, "Bayar Tagihan Listrik: Rp%.2f", jumlah_tagihan);
        addToHistory(operation);
        printf("Tagihan listrik berhasil dibayar.\n");
    }
    return saldo;
}

float payPlaneTicket(float saldo) {
    float jumlah_tagihan;
    printf("Masukkan jumlah pembayaran tiket pesawat: Rp");
    if (scanf("%f", &jumlah_tagihan) != 1 || jumlah_tagihan < 0) {
        printf("Input tidak valid. Harap masukkan angka yang valid.\n");
        while (getchar() != '\n');
        return saldo;
    }
    if (jumlah_tagihan > saldo) {
        printf("Saldo tidak mencukupi untuk pembayaran tiket pesawat.\n");
    } else {
        saldo -= jumlah_tagihan;
        char operation[50];
        sprintf(operation, "Bayar Tiket Pesawat: Rp%.2f", jumlah_tagihan);
        addToHistory(operation);
        printf("Pembayaran tiket pesawat berhasil.\n");
    }
    return saldo;
}

float payTrainTicket(float saldo) {
    float jumlah_tagihan;
    printf("Masukkan jumlah pembayaran tiket kereta api: Rp");
    if (scanf("%f", &jumlah_tagihan) != 1 || jumlah_tagihan < 0) {
        printf("Input tidak valid. Harap masukkan angka yang valid.\n");
        while (getchar() != '\n');
        return saldo;
    }
    if (jumlah_tagihan > saldo) {
        printf("Saldo tidak mencukupi untuk pembayaran tiket kereta api.\n");
    } else {
        saldo -= jumlah_tagihan;
        char operation[50];
        sprintf(operation, "Bayar Tiket Kereta Api: Rp%.2f", jumlah_tagihan);
        addToHistory(operation);
        printf("Pembayaran tiket kereta api berhasil.\n");
    }
    return saldo;
}

float payHotel(float saldo) {
    float jumlah_tagihan;
    printf("Masukkan jumlah pembayaran hotel: Rp");
    if (scanf("%f", &jumlah_tagihan) != 1 || jumlah_tagihan < 0) {
        printf("Input tidak valid. Harap masukkan angka yang valid.\n");
        while (getchar() != '\n');
        return saldo;
    }
    if (jumlah_tagihan > saldo) {
        printf("Saldo tidak mencukupi untuk pembayaran hotel.\n");
    } else {
        saldo -= jumlah_tagihan;
        char operation[50];
        sprintf(operation, "Bayar Hotel: Rp%.2f", jumlah_tagihan);
        addToHistory(operation);
        printf("Pembayaran hotel berhasil.\n");
    }
    return saldo;
}

float buyCredit(float saldo) {
    float jumlah;
    printf("Masukkan jumlah pembelian pulsa: Rp");
    if (scanf("%f", &jumlah) != 1 || jumlah < 0) {
        printf("Input tidak valid. Harap masukkan angka yang valid.\n");
        while (getchar() != '\n');
        return saldo;
    }
    if (jumlah > saldo) {
        printf("Saldo tidak mencukupi untuk pembelian pulsa.\n");
    } else {
        saldo -= jumlah;
        char operation[50];
        sprintf(operation, "Beli Pulsa: Rp%.2f", jumlah);
        addToHistory(operation);
        printf("Pembelian pulsa berhasil.\n");
    }
    return saldo;
}

void displayTransactionHistory() {
    displayHistory();
}

void showQRIS() {
    printf("  Qris Budi \n");
    printf("-=-[=-][==-[\n");
    printf("[==-][=-[=-]\n");
    printf("][=-][=-=[=-\n");
}

float transferAntarBank(float saldo) {
    // Implementasi transfer antar bank
    printf("Fitur transfer antar bank belum tersedia.\n");
    return saldo;
}



int main() {
    char kode_akses[10];
    float saldo = 1000000;
    int pilihan;
    
    do {
        printf("User BCA : Budi\n");
        printf("Kode Akses: wca123\n");
        printf("Masukkan Kode Akses: ");
        scanf("%s", kode_akses);
        
        if(strcmp(kode_akses, "wca123") != 0)
            printf("Kode akses salah. Silakan coba lagi.\n");

    } while (strcmp(kode_akses, "wca123") != 0);
    
    do {
        displayMenu();
        printf("Pilih menu: ");
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid. Harap masukkan angka.\n");
            while (getchar() != '\n');
            continue;
        }
        switch (pilihan) {
            case 1:
                checkBalance(saldo);
                break;
            case 2:
                saldo = deposit(saldo);
                break;
            case 3:
                saldo = withdraw(saldo);
                break;
            case 4:
                transfer(&saldo, &saldo);
                break;
            case 5:
                transfer(&saldo, &saldo);
                break;
            case 6:
                saldo = topUpFlazz(saldo);
                break;
            case 7:
                saldo = bayarTagihanListrik(saldo);
                break;
            case 8:
    printf("Pilih jenis pembayaran:\n");
    printf("1. Tiket Pesawat\n");
    printf("2. Tiket Kereta Api\n");
    printf("3. Hotel\n");
    printf("Pilihan: ");
    int jenis_pembayaran;
    if (scanf("%d", &jenis_pembayaran) != 1) {
        printf("Input tidak valid. Harap masukkan angka.\n");
        while (getchar() != '\n');
        break;
    }
    switch (jenis_pembayaran) {
        case 1:
            saldo = payPlaneTicket(saldo);
            break;
        case 2:
            saldo = payTrainTicket(saldo);
            break;
        case 3:
            saldo = payHotel(saldo);
            break;
        default:
            printf("Pilihan tidak valid.\n");
    }
    break;
        case 9:
            saldo = buyCredit(saldo);
            break;
        case 10:
            displayTransactionHistory();
            
            saveTransactionHistoryToFile();
            break;
        case 11:
            showQRIS();
            break;
        case 12:
            printf("Terima kasih telah menggunakan layanan Warkop Central Asia.\n");
            break;
        default:
            printf("Pilihan tidak valid.\n");
    }
} while (pilihan != 12);
return 0;
}

