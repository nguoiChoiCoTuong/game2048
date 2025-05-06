#include<iostream>
#include<cstdlib> //Thư viện cho hàm rand()
#include<ctime> //Thư viện cho hàm time()
using namespace std;
void menu();
void printMatrix(int matrix[4][4]);

void rowToArray(int matrix[4][4], int array[4], int row_i);
void colToArray(int matrix[4][4], int array[4], int col_j);
void arrayToRow(int matrix[4][4], int array[4], int row_i);
void arrayToCol(int matrix[4][4], int array[4], int col_j);

void moveLeft1D(int array[4]);
void moveRight1D(int array[4]);

void moveLeft2D(int matrix[4][4]);
void moveRight2D(int matrix[4][4]);
void moveUp2D(int matrix[4][4]);
void moveDown2D(int matrix[4][4]);

bool checkMatrix(int matrix[4][4]);
bool compareMatrix(int matrixA[4][4], int matrixB[4][4]);

bool randomCell(int matrix[4][4]);
int main(){
    srand(time(0)); //Khởi tạo seed;
    int matrix[4][4]={};
    randomCell(matrix);
    printMatrix(matrix);
    int n=1;
    while(n){
        menu();
        cout<<"\nMoi ban nhap: ";
        cin>>n;
        if(n==1){
            moveRight2D(matrix);
        }else if(n==2){
            moveLeft2D(matrix);
        }else if(n==3){
            moveUp2D(matrix);
        }else if(n==4){
            moveDown2D(matrix);
        }
        bool random=randomCell(matrix);
        if(random){
            printMatrix(matrix);
        }else{
            n=0;
            cout<<"\nTro choi ket thuc";
        }
    }

}
void menu(){
    cout<<"\n------MENU-----";
    cout<<"\n1-Di chuyen phai";
    cout<<"\n2-Di chuyen trai";
    cout<<"\n3-Di chuyen len";
    cout<<"\n4-Di chuyen xuong";
    cout<<"\n0-Thoat game";
    cout<<"\n-------------------";
}
void printMatrix(int matrix[4][4]){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}
void moveLeft1D(int array[4]){
    int newArray[4]={};
    int j=0, temp=array[0];
    for(int i=1;i<4;i++){
        if(array[i]==temp && temp!=0){
            newArray[j++]=2*temp;
            temp=0;
        }else{
            if(temp!=0 && array[i]!=0){
                newArray[j++]=temp;
            }
            if(array[i]!=0) temp=array[i];
        }
    }
    newArray[j]=temp;
    for(int i=0;i<4;i++){
        array[i]=newArray[i];
    }
}
void moveRight1D(int array[4]){
    int newArray[4]={};
    int temp=array[3], j=0;
    for(int i=2;i>=0;i--){
        if(array[i]==temp && temp!=0){
            newArray[j++]=2*temp; //Lưu mảng từ trái qua phải
            temp=0;
        }else{
            if(temp!=0 && array[i]!=0){
                newArray[j++]=temp;
            }
            if(array[i]!=0) temp=array[i];
        }
    }
    newArray[j]=temp;
    //Đảo ngược mảng lại
    for(int i=0;i<4;i++){
        array[i]=newArray[3-i];
    }
}
void rowToArray(int matrix[4][4], int array[4], int row_i){
    for(int j=0;j<4;j++){
        array[j]=matrix[row_i][j];
    }
}
void colToArray(int matrix[4][4], int array[4], int col_j){
    for(int i=0;i<4;i++){
        array[i]=matrix[i][col_j];
    }
}
void arrayToRow(int matrix[4][4], int array[4], int row_i){
    for(int j=0;j<4;j++){
        matrix[row_i][j]=array[j];
    }
}
void arrayToCol(int matrix[4][4], int array[4], int col_j){
    for(int i=0;i<4;i++){
        matrix[i][col_j]=array[i];
    }
}
void moveLeft2D(int matrix[4][4]){
    for(int i=0;i<4;i++){
        int array[4]={};
        rowToArray(matrix,array,i);
        moveLeft1D(array);
        arrayToRow(matrix,array,i);
    }
}
void moveRight2D(int matrix[4][4]){
    for(int i=0;i<4;i++){
        int array[4]={};
        rowToArray(matrix,array,i);
        moveRight1D(array);
        arrayToRow(matrix,array,i);
    }
}
void moveUp2D(int matrix[4][4]){
    for(int j=0;j<4;j++){
        int array[4]={};
        colToArray(matrix,array,j);
        moveLeft1D(array);
        arrayToCol(matrix,array,j);
    }
}
void moveDown2D(int matrix[4][4]){
    for(int j=0;j<4;j++){
        int array[4]={};
        colToArray(matrix,array,j);
        moveRight1D(array);
        arrayToCol(matrix,array,j);
    }
}
bool compareMatrix(int matrixA[4][4], int matrixB[4][4]){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(matrixA[i][j]!=matrixB[i][j]) return false;
        }
    }
    return true;
}
bool checkMatrix(int matrix[4][4]){
    int matrixTemp[4][4]={};
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            matrixTemp[i][j]=matrix[i][j];
        }
    }
    moveLeft2D(matrixTemp);
    if(compareMatrix(matrixTemp,matrix)) return true;
    moveRight2D(matrixTemp);
    if(compareMatrix(matrixTemp,matrix)) return true;
    moveUp2D(matrixTemp);
    if(compareMatrix(matrixTemp,matrix)) return true;
    moveDown2D(matrixTemp);
    if(compareMatrix(matrixTemp,matrix)) return true;
    return false;
}
bool randomCell(int matrix[4][4]){
    int space[20][2];
    int blank=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(matrix[i][j]==0){
                space[blank][0]=i;
                space[blank++][1]=j;
            }
        }
    }
    if(blank==0){
        if(!checkMatrix(matrix)) return false;
        return true;
    }
    int chosenCell= rand() % blank;
    float percent=(rand() % 10 /10.0);
    int row=space[chosenCell][0];
    int col=space[chosenCell][1];
    if(percent>0.5){
        matrix[row][col]=4;
    }else{
        matrix[row][col]=2;
    }
    return true;
}
