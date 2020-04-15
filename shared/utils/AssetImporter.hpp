#include "../beatsaber-hook/shared/utils/utils.h"
#include <functional>

class AssetImporter : public Il2CppObject {
public:
    Il2CppString* assetFilePath = nullptr;
    Il2CppString* assetName = nullptr;
    Il2CppObject* assetType = nullptr;
    std::function<void(AssetImporter*)> whenDone;

    bool pathExists = false;
    bool LoadedAssetBundle() const { return assetBundle; }
    bool LoadedAsset() const { return asset; }

    AssetImporter(std::string_view assetBundlePath) {
        assetFilePath = CRASH_UNLESS(il2cpp_utils::createcsstr(assetBundlePath));
        pathExists = *CRASH_UNLESS(il2cpp_utils::RunMethod<bool>("System.IO", "File", "Exists", assetFilePath));
    }

    AssetImporter(std::string_view assetBundlePath, std::string_view assetNameS, std::string_view assetNamespace = "UnityEngine",
        std::string_view assetClassName = "GameObject")
    : AssetImporter(assetBundlePath) {
        assetName = CRASH_UNLESS(il2cpp_utils::createcsstr(assetNameS));
        SetNextAssetType(assetNamespace, assetClassName);
    }

    // Returns true if the asset bundle load has been requested, false otherwise
    bool LoadAssetBundle(bool alsoLoadAsset = false);
    bool SetNextAssetType(std::string_view assetNamespace, std::string_view assetClassName) {
        // TODO: instantly return true if assetType is already set to these params
        if (assetAsync && !asset)
            return false;
        assetType = RET_0_UNLESS(il2cpp_utils::GetSystemType(assetNamespace, assetClassName));
        assetAsync = nullptr;
        asset = nullptr;
        return true;
    }
    // Returns true if the asset is (now) loading async, false otherwise
    bool LoadAsset(std::string_view assetNameS = "");
    // Returns true if the callback was stored, false if it was immediately called
    bool RegisterOrDoCallback(decltype(whenDone) callback) {
        if (LoadedAsset()) {
            callback(this);
            return false;
        } else {
            whenDone = callback;
            return true;
        }
    }
    // If there is an asset loaded, returns a copy of it.
    Il2CppObject* InstantiateAsset() const;

private:
    Il2CppObject* bundleAsync = nullptr;
    Il2CppObject* assetBundle = nullptr;
    Il2CppObject* assetAsync = nullptr;
    Il2CppObject* asset = nullptr;
    bool permissionToLoadAsset = false;

    static void AssetBundleComplete(AssetImporter* obj, Il2CppObject* asyncOp);
    static void AssetComplete(AssetImporter* obj, Il2CppObject* asyncOp);
};
