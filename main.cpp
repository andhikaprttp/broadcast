#include <iostream>
#include <string>
#include <sstream>
#include <bitset>

using namespace std;

int main()
{
    string ip_address, subnet_mask;
    cout << "Program Menghitung Broadcast" << endl;
    cout << "============================" << endl;
     // SMK RADEN PAKU TEKNIK KOMPUTER DAN JARINGAN 
    cout << "Masukkan alamat IP (contoh: 192.168.1.100): ";
    getline(cin, ip_address);
    cout << "Masukkan subnet mask (contoh: 255.255.255.0): ";
    getline(cin, subnet_mask);

    // Memisahkan oktet-oktet IP dan subnet mask menjadi array of string
    string ip_octet[4];
    string subnet_octet[4];
    stringstream ss(ip_address);
    for (int i = 0; i < 4; i++) {
        getline(ss, ip_octet[i], '.');
    }
    stringstream ss2(subnet_mask);
    for (int i = 0; i < 4; i++) {
        getline(ss2, subnet_octet[i], '.');
    }

    // Mengubah oktet-oktet IP dan subnet mask menjadi bilangan biner
    bitset<8> ip_bin[4];
    bitset<8> subnet_bin[4];
    for (int i = 0; i < 4; i++) {
        ip_bin[i] = bitset<8>(ip_octet[i]);
        subnet_bin[i] = bitset<8>(subnet_octet[i]);
    }

    // Menghitung alamat network dari IP dan subnet mask
    bitset<32> network_bin;
    for (int i = 0; i < 32; i++) {
        if (i < 24) {
            network_bin[i] = ip_bin[i].to_ulong() & subnet_bin[i].to_ulong();
        } else {
            network_bin[i] = 0;
        }
    }

    // Menghitung alamat broadcast dari alamat network dan subnet mask
    bitset<32> broadcast_bin;
    bitset<32> complement_mask;
    for (int i = 0; i < 32; i++) {
        complement_mask[i] = ~subnet_bin[i % 8];
        broadcast_bin[i] = network_bin[i] | complement_mask[i];
    }

    // Mengubah alamat broadcast dari bilangan biner menjadi desimal
    string broadcast_octet[4];
    for (int i = 0; i < 4; i++) {
        broadcast_octet[i] = to_string(broadcast_bin.to_ulong() >> (i * 8) & 255);
    }

    // Menampilkan alamat broadcast
    cout << "Alamat broadcast: " << broadcast_octet[0] << "." << broadcast_octet[1] << "." << broadcast_octet[2] << "." << broadcast_octet[3] << endl;

    return 0;
}
