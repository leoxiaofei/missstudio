#ifndef PUBKEY_H__
#define PUBKEY_H__

#include <string.h>
#include <stddef.h>
#include <wtypes.h>


class PubKey {
protected:
	int		keyLen;
	int		e;
	int		capa;
	BYTE	*key;

public:
	PubKey(void) { key = NULL; keyLen = 0; e = 0; capa = 0; }
	~PubKey() { UnSet(); }

	// ´úÈëŒê
	PubKey(const PubKey& o) { PubKey(); *this = o; }
	PubKey &operator=(const PubKey &o) {
		Set(o.key, o.keyLen, o.e, o.capa);
		return	*this;
	}

	void Set(BYTE *_key, int len, int _e, int _capa) {
		UnSet(); e = _e; capa = _capa; key = new BYTE [keyLen=len]; memcpy(key, _key, len);
	}
	void UnSet(void) {
		delete [] key; key = NULL; keyLen = 0; e = 0; capa = 0;
	}
	const BYTE *Key(void) { return key; }
	int KeyLen(void) { return keyLen; }
	int Exponent(void) { return e; }
	BOOL KeyBlob(BYTE *blob, int maxLen, int *len) {
		if ((*len = KeyBlobLen()) > maxLen) return FALSE;
		/* PUBLICSTRUC */	blob[0] = PUBLICKEYBLOB; blob[1] = CUR_BLOB_VERSION;
		*(WORD *)(blob+2) = 0; *(ALG_ID *)(blob+4) = CALG_RSA_KEYX;
		/* RSAPUBKEY */		memcpy(blob+8, "RSA1", 4);
		*(DWORD *)(blob+12) = keyLen * 8; *(int *)(blob+16) = e;
		/* PUBKEY_DATA */	memcpy(blob+20, key, keyLen);
		return	TRUE;
	}
	int KeyBlobLen(void) { return keyLen + 8 + 12; /* PUBLICKEYSTRUC + RSAPUBKEY */ }
	void SetByBlob(BYTE *blob, int _capa) {
		UnSet();
		keyLen = *(int *)(blob+12) / 8;
		key = new BYTE [keyLen];
		memcpy(key, blob+20, keyLen);
		e = *(int *)(blob+16);
		capa = _capa;
	}
	int Capa(void) { return capa; }

	int Serialize(BYTE *buf, int size) {
		int	offset = offsetof(PubKey, key);
		if (offset + keyLen > size) return -1;
		memcpy(buf, this, offset);
		if (keyLen > 0) memcpy(buf + offset, key, keyLen);
		return	offset + keyLen;
	}
	BOOL UnSerialize(BYTE *buf, int size) {
		int	offset = offsetof(PubKey, key);
		if (offset >= size) return FALSE;
		PubKey	*k = (PubKey *)buf;
		if (k->keyLen + offset != size) return FALSE;
		UnSet();
		Set((BYTE *)&k->key, k->keyLen, k->e, k->capa);
		return	TRUE;
	}
};

#endif // PUBKEY_H__
