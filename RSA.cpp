#include "RSA.h"

class RSA {
private:
	ZZ privatekey;
	ZZ phi;


public:
	ZZ publickey;
	ZZ mod;

	RSA(long nbits) {
		ZZ p, q;
		p = generate_long_number(nbits);
		q = generate_long_number(nbits);
		this->mod = p * q;
		this->phi = (p-1) * (q-1);
		this->publickey = publickey_generator(this->phi);
		this->privatekey = privatekey_generator(this->privatekey, this->phi);

		cout << "p: " << p << endl << endl;
		cout << "NumBytes(p): " << NumBytes(p) << endl << endl;
		cout << "q: " << q << endl << endl;
		// cout << "mod: " << mod << endl << endl;
		// cout << "phi: " << phi << endl << endl;
		// cout << "publickey: " << publickey << endl << endl;
		// cout << "privatekey: " << privatekey << endl << endl;
	}

	~RSA() {
		publickey.kill();
		privatekey.kill();
		mod.kill();
		phi.kill();
	}

	string encrypt(string text) {
		string out;
		for (int i = 0; i < text.size(); i++) {
			ZZ C, M;
			M = text[i];
			C = modular_exponentiation(M, publickey, mod);
			//out += C;
		}

		return out;
	}

	string decrypt(string text) {
		string out;
		for (int i = 0; i < text.size(); i++) {
			ZZ C, M;
			C = text[i];
			M = modular_exponentiation(C, privatekey, mod);
			//out += M;
		}

		return out;
	}

private:
	ZZ find_large_prime(long nbits) {
	}

	ZZ generate_long_number(long nbits) {
		ZZ minimum;
		long a = 2;
		long b = 500;
		power(minimum, a, b);
		ZZ random = RandomLen_ZZ(2*nbits);

		return random;
	}

	ZZ publickey_generator(ZZ phi) {
		ZZ e, a;
		a = 2;
		long b = 16;
		e = power(a, b) + 1;

		return e;
	}

	ZZ privatekey_generator(ZZ e, ZZ phi) {
		ZZ d;
		InvModStatus(d, e, phi);
		
		return d;
	}

	ZZ mdc(ZZ &a, ZZ &b) {
		ZZ r = a%b;

		if (a < b) {
			a ^= b;
			b ^= a;
			a ^= b;
		}

		while (r > 0) {
			a = b;
			b = r;
			r = a%b;
		}

		return b;
	}

public:
	// returns: res = a^b mod(n)
	ZZ modular_exponentiation(ZZ &a, ZZ &b, ZZ &n) {
		ZZ res;
		res = 1;

		while (b > 0) {
			if (compare(b&1, 0) > 0) {
				res = (res*a)%n;
			}
			b >>= 1;
			a = (a*a)%n;
		}

		return res;
	}

};
