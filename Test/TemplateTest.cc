

template<typename T>
void foo(T value) {
    printf("%d ", value);
}

template void foo(float value);

int main() {
    // foo(5);
}