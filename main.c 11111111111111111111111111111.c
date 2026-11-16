#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int main()
{
    int saglik = 100;
    int enerji = 100;
    int oksijen = 100;
    int su = 30;
    int parca = 3;
    int modulHasari = 20;
    int kilitMuhurlu = 0;

    int gun = 1;
    int tur = 0;
    int puan;

    int zar, esik;
    int miktar, uretilen;
    int i, sure;
    int deneme, sifre;
    int toplamHasar, toplamSaglikKaybi;
    int toplamOksijenKaybi;
    int eskiSaglik, eskiOksijen;
    int hasarAlinanTur;
    int oyunBitti = 0;

    char zorluk, komut, girilenSifre;

    srand(time(NULL));

    printf("====================================\n");
    printf(" MARS KOLONISI YASAM DESTEK OYUNU\n");
    printf("====================================\n");

    /* Zorluk seviyesi secimi */

    do
    {
        printf("\nZorluk seciniz:\n");
        printf("K - Kolay\n");
        printf("N - Normal\n");
        printf("Z - Zor\n");
        printf("Seciminiz: ");

        scanf(" %c", &zorluk);
        zorluk = toupper(zorluk);

        switch(zorluk)
        {
            case 'K':
                su = 40;
                parca = 5;
                modulHasari = 10;
                printf("Kolay seviye secildi.\n");
                break;

            case 'N':
                su = 30;
                parca = 3;
                modulHasari = 20;
                printf("Normal seviye secildi.\n");
                break;

            case 'Z':
                su = 20;
                parca = 2;
                modulHasari = 30;
                printf("Zor seviye secildi.\n");
                break;

            default:
                printf("Gecersiz secim! Tekrar deneyin.\n");
        }

    } while(zorluk != 'K' && zorluk != 'N' && zorluk != 'Z');

    if(zorluk == 'K')
        sure = 3;
    else if(zorluk == 'N')
        sure = 5;
    else
        sure = 7;

    printf("\nKurtarma ekibi 15. gun gelecek!\n");
    printf("Hayatta kalmak icin komutlari kullanin.\n");

    /* Ana oyun dongusu */

    do
    {
        printf("\n========== KOMUTLAR ==========\n");
        printf("G - Kesif\n");
        printf("O - Oksijen uret\n");
        printf("T - Tamir\n");
        printf("D - Durum raporu\n");
        printf("U - Uyu / Dinlen\n");
        printf("K - Kum firtinasi\n");
        printf("H - Hava kilidini muhurlendir\n");
        printf("Q - Cikis\n");

        printf("\nKomutunuz: ");
        scanf(" %c", &komut);
        komut = toupper(komut);

        eskiSaglik = saglik;
        eskiOksijen = oksijen;

        switch(komut)
        {
            /* KESIF */

            case 'G':
            {
                if(enerji < 15 || oksijen < 10)
                {
                    printf("Kesif icin yeterli kaynak yok!\n");
                    break;
                }

                enerji = enerji - 15;
                oksijen = oksijen - 10;

                if(enerji > 40 && oksijen > 30)
                    esik = 65;
                else
                    esik = 30;

                zar = rand() % 100;

                printf("Su bulma zari: %d / Esik: %d\n", zar, esik);

                if(zar < esik)
                {
                    su = su + 5;
                    printf("Kesifte 5 birim su buldunuz!\n");
                }
                else
                {
                    printf("Su bulunamadi.\n");
                }

                zar = rand() % 100;
                esik = 35;

                printf("Parca bulma zari: %d / Esik: %d\n", zar, esik);

                if(zar < esik)
                {
                    parca = parca + 1;
                    printf("1 yedek parca buldunuz!\n");
                }
                else
                {
                    printf("Yedek parca bulunamadi.\n");
                }

                zar = rand() % 100;

                printf("Yaralanma zari: %d / Esik: 10\n", zar);

                if(zar < 10 || modulHasari > 70)
                {
                    saglik = saglik - 15;
                    printf("Kesif sirasinda yaralandiniz!\n");
                }
                else
                {
                    printf("Kesif sirasinda yaralanmadiniz.\n");
                }

                break;
            }

            /* OKSIJEN URETIMI */

            case 'O':
            {
                if(enerji < 5)
                {
                    printf("Oksijen uretmek icin enerji yetersiz!\n");
                    break;
                }

                printf("Kullanilacak su miktari: ");
                scanf("%d", &miktar);

                if(miktar < 0 || miktar > su)
                {
                    printf("Gecersiz su miktari!\n");
                    break;
                }

                if(miktar % 2 == 1)
                {
                    uretilen = (miktar - 1) / 2 * 3;
                    printf("1 birim su artik olarak kaldi.\n");
                }
                else
                {
                    uretilen = miktar / 2 * 3;
                }

                if(oksijen + uretilen > 100)
                {
                    printf("Oksijen kapasitesi asiliyor!\n");
                    break;
                }

                su = su - (miktar - (miktar % 2));
                oksijen = oksijen + uretilen;
                enerji = enerji - 5;

                printf("%d birim oksijen uretildi.\n", uretilen);

                break;
            }

            /* TAMIR */

            case 'T':
            {
                if(enerji < 10)
                {
                    printf("Tamir icin enerji yetersiz!\n");
                    break;
                }

                if(parca <= 0)
                {
                    printf("Yedek parca bulunmuyor!\n");
                    break;
                }

                if(modulHasari == 0)
                {
                    printf("Modul zaten saglam.\n");
                    break;
                }

                if(modulHasari <= 30)
                {
                    modulHasari = modulHasari - 20;
                    parca = parca - 1;
                    printf("Hafif hasar onarildi.\n");
                }
                else if(modulHasari <= 70)
                {
                    modulHasari = modulHasari - 15;
                    parca = parca - 1;
                    printf("Orta hasar onarildi.\n");
                }
                else
                {
                    modulHasari = modulHasari - 10;
                    parca = parca - 1;
                    printf("Agir hasar onarildi.\n");
                }

                enerji = enerji - 10;

                break;
            }

            /* DURUM RAPORU */

            case 'D':
            {
                printf("\n========== DURUM RAPORU ==========\n");

                printf("Saglik: %d\n", saglik);
                printf("Enerji: %d\n", enerji);
                printf("Oksijen: %d\n", oksijen);
                printf("Su: %d\n", su);
                printf("Yedek parca: %d\n", parca);
                printf("Modul hasari: %d\n", modulHasari);
                printf("Kilit muhurlu: %d\n", kilitMuhurlu);
                printf("Gun: %d\n", gun);
                printf("Tur: %d\n", tur);

                if(oksijen < 25)
                    printf("UYARI: Oksijen kritik seviyede!\n");

                if(saglik < 30)
                    printf("UYARI: Saglik kritik seviyede!\n");

                if(modulHasari > 70)
                    printf("UYARI: Modul hasari cok yuksek!\n");

                if(su < 5)
                    printf("UYARI: Su miktari az!\n");

                if(saglik >= 30 && oksijen >= 25 &&
                   modulHasari <= 70 && su >= 5)
                {
                    printf("TUM SISTEMLER NORMAL.\n");
                }

                break;
            }

            /* DINLENME */

            case 'U':
            {
                if(enerji > 80)
                    enerji = 100;
                else
                    enerji = enerji + 20;

                if(oksijen >= 20)
                {
                    if(saglik > 85)
                        saglik = 100;
                    else
                        saglik = saglik + 15;

                    printf("Dinlendiniz, sagliginiz artti.\n");
                }
                else
                {
                    saglik = saglik - 10;
                    printf("Oksijen az! Dinlenirken saglik kaybettiniz.\n");
                }

                break;
            }

            /* KUM FIRTINASI */

            case 'K':
            {
                toplamHasar = 0;
                toplamSaglikKaybi = 0;
                toplamOksijenKaybi = 0;
                hasarAlinanTur = 0;

                printf("\nKUM FIRTINASI BASLADI!\n");

                for(i = 1; i <= sure; i++)
                {
                    zar = rand() % 100;

                    printf("\n%d. Tur - Zar: %d / Esik: 40\n", i, zar);

                    if(kilitMuhurlu == 1 && zar >= 40 && zar < 70)
                    {
                        printf("Muhurlu kilit sayesinde sizinti engellendi.\n");
                        continue;
                    }

                    if(zar < 30)
                    {
                        int kayip = 5;

                        if(i % 2 == 0)
                            kayip = kayip * 2;

                        saglik = saglik - kayip;
                        toplamSaglikKaybi = toplamSaglikKaybi + kayip;
                        hasarAlinanTur++;

                        printf("Can kaybi: %d\n", kayip);
                    }
                    else if(zar < 70)
                    {
                        int kayip = 10;

                        if(i % 2 == 0)
                            kayip = kayip * 2;

                        oksijen = oksijen - kayip;
                        toplamOksijenKaybi = toplamOksijenKaybi + kayip;
                        hasarAlinanTur++;

                        printf("Oksijen sizintisi: %d\n", kayip);
                    }
                    else if(zar < 90)
                    {
                        int hasar = 5;

                        if(i % 2 == 0)
                            hasar = hasar * 2;

                        modulHasari = modulHasari + hasar;
                        toplamHasar = toplamHasar + hasar;
                        hasarAlinanTur++;

                        printf("Modul hasari: %d\n", hasar);
                    }
                    else
                    {
                        printf("Firtinadan zarar gormediniz.\n");
                    }

                    if(saglik <= 0 || oksijen <= 0)
                        break;
                }

                printf("\nFIRTINA RAPORU\n");
                printf("Hasar alinan tur: %d\n", hasarAlinanTur);
                printf("Toplam saglik kaybi: %d\n", toplamSaglikKaybi);
                printf("Toplam oksijen kaybi: %d\n", toplamOksijenKaybi);
                printf("Toplam modul hasari: %d\n", toplamHasar);

                break;
            }

            /* HAVA KILIDI SIFRESI */

            case 'H':
            {
                if(kilitMuhurlu == 1)
                {
                    printf("Hava kilidi zaten muhurlu.\n");
                    break;
                }

                sifre = 'A' + (gun % 26);
                deneme = 0;
                girilenSifre = ' ';

                printf("Ipucu: Sifre A harfinden bugunun gun sayisi kadar ileridedir.\n");

                do
                {
                    printf("Sifreyi girin: ");
                    scanf(" %c", &girilenSifre);

                    girilenSifre = toupper(girilenSifre);
                    deneme++;

                    if(girilenSifre != sifre)
                    {
                        enerji = enerji - 5;

                        if(girilenSifre < sifre)
                            printf("Daha ileri git!\n");
                        else
                            printf("Geri git!\n");

                        printf("Zar: %d / Esik: Dogru karakter\n", deneme);
                    }
                    else
                    {
                        kilitMuhurlu = 1;
                        printf("Hava kilidi basariyla muhurlendi!\n");
                    }

                } while(girilenSifre != sifre && deneme < 3);

                if(kilitMuhurlu == 0)
                {
                    modulHasari = modulHasari + 20;
                    printf("Uc deneme basarisiz! Modul hasari artti.\n");
                }

                break;
            }

            /* CIKIS */

            case 'Q':
            {
                printf("Oyundan cikiliyor.\n");
                oyunBitti = 1;
                break;
            }

            default:
            {
                printf("Gecersiz komut! Tekrar deneyin.\n");
                break;
            }
        }

        /* Gecersiz komut ve durum raporu tur harcamaz */

        if(komut == 'D' ||
           (komut != 'G' && komut != 'O' && komut != 'T' &&
            komut != 'U' && komut != 'K' && komut != 'H' &&
            komut != 'Q'))
        {
            continue;
        }

        if(komut == 'Q')
            break;

        /* Degerlerin sinirlandirilmasi */

        if(saglik < 0)
            saglik = 0;
        if(saglik > 100)
            saglik = 100;

        if(enerji < 0)
            enerji = 0;
        if(enerji > 100)
            enerji = 100;

        if(oksijen < 0)
            oksijen = 0;
        if(oksijen > 100)
            oksijen = 100;

        if(modulHasari < 0)
            modulHasari = 0;
        if(modulHasari > 100)
            modulHasari = 100;

        if(su < 0)
            su = 0;
        if(parca < 0)
            parca = 0;

        /* Tur ve gun kontrolu */

        tur++;

        if(tur % 3 == 0)
        {
            gun++;
            oksijen = oksijen - 8;

            printf("\nYENI GUN: %d\n", gun);
            printf("Gun baslangicinda 8 oksijen tuketildi.\n");

            if(modulHasari > 70)
            {
                saglik = saglik - 5;
                printf("Yuksek modul hasari nedeniyle 5 saglik kaybettiniz.\n");
            }
        }

        if(saglik < 0)
            saglik = 0;
        if(oksijen < 0)
            oksijen = 0;

        printf("\nSaglik: %d | Enerji: %d | Oksijen: %d\n",
               saglik, enerji, oksijen);

        if(saglik <= 0 || oksijen <= 0)
        {
            printf("\nHAYATTA KALAMADINIZ!\n");
            oyunBitti = 1;
        }

        if(gun >= 15 && oyunBitti == 0)
        {
            printf("\nKURTARMA EKIBI GELDI! KAZANDINIZ!\n");
            oyunBitti = 1;
        }

    } while(oyunBitti == 0);

    /* OYUN SONU RAPORU */

    puan = (gun * 100) + saglik + oksijen - modulHasari;

    printf("\n====================================\n");
    printf("          OYUN SONU RAPORU\n");
    printf("====================================\n");

    printf("Hayatta kalinan gun: %d\n", gun);
    printf("Toplam tur: %d\n", tur);
    printf("Son saglik: %d\n", saglik);
    printf("Son enerji: %d\n", enerji);
    printf("Son oksijen: %d\n", oksijen);
    printf("Son su: %d\n", su);
    printf("Son yedek parca: %d\n", parca);
    printf("Son modul hasari: %d\n", modulHasari);
    printf("Puan: %d\n", puan);

    printf("\nSimulasyon sona erdi.\n");

    return 0;
}
