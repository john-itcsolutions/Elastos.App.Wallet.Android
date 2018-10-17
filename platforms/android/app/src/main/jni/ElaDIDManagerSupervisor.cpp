// Copyright (c) 2012-2018 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ElaUtils.h"
#include "DIDManagerSupervisor.h"

using namespace Elastos::ElaWallet;
using namespace Elastos::DID;

#define SIG_NEW_IDMANAGER_SUPERVISOR "(Ljava/lang/String;)J"
static jlong JNICALL nativeNewDIDManagerSupervisor(JNIEnv *env, jobject clazz, jstring jrootPath)
{
	bool exception = false;
	std::string msgException;

	const char* rootPath = env->GetStringUTFChars(jrootPath, NULL);
	DIDManagerSupervisor *supervisor = NULL;

	try {
		supervisor = new DIDManagerSupervisor(rootPath);
	} catch (std::exception &e) {
		exception = true;
		msgException = e.what();
	}

	if (exception) {
		ThrowWalletException(env, msgException.c_str());
	}

	return (jlong) supervisor;
}

#define SIG_DISPOSE_NATIVE "(J)V"
static void JNICALL nativeDisposeNative(JNIEnv *env, jobject clazz, jlong jSupervisor)
{
	bool exception = false;
	std::string msgException;

	try {
		DIDManagerSupervisor *supervisor = (DIDManagerSupervisor *) jSupervisor;
		delete supervisor;
	} catch (std::exception &e) {
		exception = true;
		msgException = e.what();
	}

	if (exception) {
		ThrowWalletException(env, msgException.c_str());
	}
}

#define SIG_CREATE_DIDMANAGER "(JJLjava/lang/String;)J"
static jlong JNICALL nativeCreateDIDManager(JNIEnv *env, jobject clazz, jlong jSupervisor,
		jlong jMasterWallet, jstring jrootPath)
{
	bool exception = false;
	std::string msgException;

	const char *rootPath = env->GetStringUTFChars(jrootPath, NULL);
	IDIDManager *manager = NULL;

	try {
		DIDManagerSupervisor *supervisor = (DIDManagerSupervisor *) jSupervisor;
		IMasterWallet *masterWallet = (IMasterWallet *) jMasterWallet;

		manager = supervisor->CreateDIDManager(masterWallet, rootPath);
	} catch (std::exception &e) {
		exception = true;
		msgException = e.what();
	}

	env->ReleaseStringUTFChars(jrootPath, rootPath);

	if (exception) {
		ThrowWalletException(env, msgException.c_str());
	}

	return (jlong)manager;
}

#define SIG_DESTROY_IDMANAGER "(JJ)V"
static void JNICALL nativeDestroyDIDManager(JNIEnv *env, jobject clazz, jlong jSupervisor,
		jlong jIDManager)
{
	bool exception = false;
	std::string msgException;

	try {
		DIDManagerSupervisor *supervisor = (DIDManagerSupervisor *) jSupervisor;
		IDIDManager *manager = (IDIDManager *) jIDManager;

		supervisor->DestroyDIDManager(manager);
	} catch (std::exception &e) {
		exception = true;
		msgException = e.what();
	}

	if (exception) {
		ThrowWalletException(env, msgException.c_str());
	}
}

static const JNINativeMethod gMethods[] = {
	{
		"nativeNewDIDManagerSupervisor",
		SIG_NEW_IDMANAGER_SUPERVISOR,
		(void *)nativeNewDIDManagerSupervisor
	},
	{
		"nativeDisposeNative",
		SIG_DISPOSE_NATIVE,
		(void *)nativeDisposeNative
	},
	{
		"nativeCreateDIDManager",
		SIG_CREATE_DIDMANAGER,
		(void *)nativeCreateDIDManager
	},
	{
		"nativeDestroyDIDManager",
		SIG_DESTROY_IDMANAGER,
		(void *)nativeDestroyDIDManager
	}
};

jint register_elastos_spv_DIDManagerSupervisor(JNIEnv *env)
{
	return jniRegisterNativeMethods(env,
			"com/elastos/spvcore/DIDManagerSupervisor",
			gMethods, NELEM(gMethods));
}
