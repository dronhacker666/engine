#include "ELib.h"

int eHashTest(){

	EHashInstance_p hash = EHash.create();

	EHash.set1i(hash, "somekey", 666);
	if( EHash.get1i(hash, "somekey") !=666 ){
		return false;
	}

	// hash in hash;
	EHashInstance_p hash2 = EHash.create();
	EHash.set1i(hash2, "somekey2", 123);

	EHash.set1p(hash, "hash2", hash2);

	EHash.dump(hash);

	return true;
}