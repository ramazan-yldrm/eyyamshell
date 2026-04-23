### 1. YAPILACAKLAR
- Built-in'ler fixlenecek
- Executor fixlenecek
- Static fonksiyonlar kontrol edilecek.
- Norminette
- 22.04.2026 ->
- mekezi hata mesajı yönetimine geçilecek
- executer ve builtinler test edilecek. Kalmışsa minik buglar da düzelecek.
### 2. YAPILANLAR
- Parser kısmında bulunan Segfault hatası düzeltildi.
- Executor'daki hatalar düzeltildi.
- Proje genelinde Norm düzenlemeleri yapıldı. (henüz tamam değil)
- Built-in'ler yazıldıç
- Executorda heredoc ele alındı.
- 22.04.2026 ->
- cleanup_and_exit önceden hata çıkıtısı da verirdi şimidi sadece temizlik çıkış yapıyor.
- şimidilik sadece executorda çalışan hata mesajı ayıklama yapısı kuruldu, istenilirse hızlı ve kolayca bütün projeye entegre edilebilir
- builtinler tamamlandı
- executer tamamlandıc
- 23.04.2026 ->
- global değişken sadece sinyalleri tutabilir çıkış bunun dışında hiçbir değer verilmemeli yoksa proje geçersiz sayılı, biz exit codlarını g_exit_status aracılığıyla tutuyorduk.
- get_set_status(int mode, int exit_code); fonksiyonu eklendi, bu fonksiyon static bir değişkenle çıkış kodlarını tutuyor. 2 moda sahip, mode parametresi "1" dışında -ki genellikle "0" kullanılır- bir değer alırsa sadece en güncel exit_status değerini döner exit_code parametresi 0(NULL) gönderilir örneğin return(get_set_status(0,0)); gibi, bu durumda last status return edilmiştir. Eğer "1" verilirse fonksiyon exit_status değerini exit_code parametresinin değeriyle değiştiriyor, örneğin: get_set_status(1, 127); son çıkış kodu 127 olmuştur. Böylece basit bir şekilde çıkış kodları işleniyor ve kritik hatadan dönülüyor o7.

### 3. AÇIKLAMALAR