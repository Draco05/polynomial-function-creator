#include <bits/stdc++.h>
using namespace std;
#define ld long double

ld calc_det(int n, ld* matrix);
ld *copy_matrix(ld *matrix, int size);
void update_matrix(ld x, int row, int size,ld *matrix);


int main(){
    int amnt_points;
    ld *matrix, *y_points, *coeficients;
    ld main_det;
    cout << "Type the amount of known points of the function: ";
    cin >> amnt_points;
    matrix = (ld*) malloc(sizeof(ld) * amnt_points * amnt_points);
    y_points = (ld*) malloc(sizeof(ld) * amnt_points);
    coeficients = (ld*) malloc(sizeof(ld) * amnt_points);
    for (int i = 0 ; i < amnt_points; i++){
        ld x, y;
        cout << "Type the x and y of the point " << i + 1 << ": ";
        cin >> x >> y;
        update_matrix(x, i, amnt_points, matrix);
        y_points[i] = y;

    }
    main_det = calc_det(amnt_points, matrix);
    if (main_det == 0){
        cout << "Not possible!\n";
        free(matrix);
        return 0;
    }
    for (int i = 0; i < amnt_points; i++){
        ld *new_matrix = copy_matrix(matrix, amnt_points);
        for (int j = 0; j < amnt_points; j++){
            new_matrix[j * amnt_points + i] = y_points[j];
        }
        coeficients[i] = calc_det(amnt_points, new_matrix) / main_det;
        free(new_matrix);
    }
    free(matrix);

    cout << "f(x) = ";
    for (int i = amnt_points - 1; i >= 0; i--){
        if (coeficients[i] == 0) continue;
        if (coeficients[i] > 0) cout << "+ ";
        else cout << "- ";
        cout << abs(coeficients[i]);
        if (i == 0) break;
        if (i == 1){
            cout << "x ";
            continue;
        }
        cout << "x^" << i << " ";
    }

    cout << '\n';

    return 0;
}

ld calc_det(int n, ld* matrix){
    if (n == 1) return matrix[0];
    
    ld sum = 0;
    for (int i = 0; i < n; i++){
        ld det;
        ld* new_matrix = (ld*) malloc((n-1) * (n-1) * sizeof(ld));
        for (int y = 1; y < n; y++){
            int aux = 0;
            for(int x = 0; x < n; x++){
                if (x == i){
                    aux += 1;
                    continue;
                }
                new_matrix[(y-1) * (n-1) + x - aux] = matrix[y * n + x];
            }
        }
        det = matrix[i] * calc_det(n-1, new_matrix); 
        free(new_matrix);
        if (i % 2) det = -det;
        sum += det;
    }
    return sum;
}

ld *copy_matrix(ld *matrix, int size){
    ld *new_matrix;
    new_matrix = (ld *) malloc(sizeof(ld) * size * size);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            new_matrix[i * size + j] = matrix[i* size + j];
        }
    }
    return new_matrix;
}

void update_matrix(ld x, int row, int size, ld *matrix){
    ld x_powers = 1;
    for (int i = 0; i < size; i++){
        matrix[size * row + i] = x_powers;
        x_powers *= x;
    }
}