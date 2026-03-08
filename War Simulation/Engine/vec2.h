#ifndef VEC2_H
#define VEC2_H

typedef struct {
    float x;
    float y;
} Vec2;

// --- Temel Aritmetik ---

// İki vektörü toplar (Pozisyon + Hız gibi)
Vec2 vec2_add(Vec2 a, Vec2 b);

// İki vektörü birbirinden çıkarır (İki nesne arası fark vektörü)
Vec2 vec2_sub(Vec2 a, Vec2 b);

// Vektörü bir sayı ile çarpar (Hız * Zaman gibi)
Vec2 vec2_mul(Vec2 v, float scalar);

// --- İleri Fiziksel İşlemler ---

// Vektörün uzunluğunu (büyüklüğünü) hesaplar (Pisagor: sqrt(x^2 + y^2))
float vec2_length(Vec2 v);

// Vektörü "birim" vektöre dönüştürür (Yönünü korur ama boyunu 1 yapar)
// Savunma sanayiinde mermi yönü hesaplarken çok kullanılır.
Vec2 vec2_normalize(Vec2 v);

// Dot Product (Noktasal Çarpım): İki vektörün ne kadar aynı yöne baktığını söyler.
float vec2_dot(Vec2 a, Vec2 b);

// İki nokta arasındaki mesafeyi hesaplar.
float vec2_distance(Vec2 a, Vec2 b);

#endif