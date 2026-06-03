#include <bits/stdc++.h>
using namespace std;

struct Barang {
    int ID;
    string nama;
    int stok;
    int harga;
    string kategori;
    string status;
};

struct BenchmarkResult {
    double buildDuration;
    double searchDuration;
    double updateDuration;
    double deleteDuration;
    int searchHits;
    long long checksum;
    size_t memoryBytes;
    size_t activeCount;
};

struct BenchmarkData {
    int itemCount;
    int queryCount;
    int rounds;
    vector<Barang> preview;
    BenchmarkResult vectorResult;
    BenchmarkResult mapResult;
};

static const vector<string> kategoriList = {
    "Elektronik", "ATK", "Kebutuhan", "Logistik", "Sparepart", "Packaging"
};

string padId(int index) {
    ostringstream output;
    output << setw(5) << setfill('0') << index;
    return output.str();
}

string getStatus(int stok) {
    if (stok == 0) return "Habis";
    if (stok < 25) return "Menipis";
    return "Tersedia";
}

string jsonEscape(const string& value) {
    ostringstream output;
    for (char ch : value) {
        switch (ch) {
            case '"': output << "\\\""; break;
            case '\\': output << "\\\\"; break;
            case '\b': output << "\\b"; break;
            case '\f': output << "\\f"; break;
            case '\n': output << "\\n"; break;
            case '\r': output << "\\r"; break;
            case '\t': output << "\\t"; break;
            default:
                output << ch;
                break;
        }
    }
    return output.str();
}

long long estimateRecordSize(const Barang& barang) {
    long long textSize = static_cast<long long>(barang.nama.size() + barang.kategori.size() + barang.status.size()) * 2;
    long long idSize = 8;
    long long numericSize = 16;
    return textSize + idSize + numericSize;
}

long long estimateVectorMemory(const vector<Barang>& records) {
    long long recordBytes = 0;
    for (const auto& barang : records) {
        recordBytes += estimateRecordSize(barang);
    }
    long long referenceBytes = static_cast<long long>(records.size()) * sizeof(Barang*);
    return recordBytes + referenceBytes + 128;
}

long long estimateMapMemory(const unordered_map<int, Barang>& records) {
    long long recordBytes = 0;
    long long keyBytes = 0;
    for (const auto& entry : records) {
        recordBytes += estimateRecordSize(entry.second);
        keyBytes += sizeof(int);
    }
    long long entryBytes = static_cast<long long>(records.size()) * 32;
    return recordBytes + keyBytes + entryBytes + 256;
}

vector<Barang> generateInventory(int count) {
    mt19937 rng(static_cast<unsigned int>(count * 97 + 13));
    uniform_real_distribution<double> unit(0.0, 1.0);
    vector<Barang> records;
    records.reserve(count);

    for (int index = 1; index <= count; ++index) {
        string idSuffix = padId(index);
        int kategoriIndex = static_cast<int>(unit(rng) * kategoriList.size());
        if (kategoriIndex >= static_cast<int>(kategoriList.size())) {
            kategoriIndex = static_cast<int>(kategoriList.size()) - 1;
        }
        int stok = static_cast<int>(unit(rng) * 160.0);
        int harga = static_cast<int>(15000.0 + unit(rng) * 485000.0);

        records.push_back({
            index,
            string("Barang ") + idSuffix,
            stok,
            harga,
            kategoriList[kategoriIndex],
            getStatus(stok)
        });
    }

    return records;
}

vector<int> createQueryIds(const vector<Barang>& records, int queryCount) {
    mt19937 rng(static_cast<unsigned int>(records.size() * 41 + queryCount * 17));
    uniform_int_distribution<int> pick(0, static_cast<int>(records.size()) - 1);
    vector<int> queryIds;
    queryIds.reserve(queryCount);

    for (int index = 0; index < queryCount; ++index) {
        queryIds.push_back(records[pick(rng)].ID);
    }

    return queryIds;
}

BenchmarkResult runVectorExperiment(const vector<Barang>& records, const vector<int>& queryIds) {
    using clockType = chrono::steady_clock;

    auto buildStart = clockType::now();
    vector<Barang> inventory = records;
    auto buildEnd = clockType::now();

    int searchHits = 0;
    long long checksum = 0;
    auto searchStart = clockType::now();
    for (int id : queryIds) {
        auto it = find_if(inventory.begin(), inventory.end(), [id](const Barang& barang) {
            return barang.ID == id;
        });
        if (it != inventory.end()) {
            ++searchHits;
            checksum += static_cast<long long>(it->harga) * it->stok;
        }
    }
    auto searchEnd = clockType::now();

    vector<int> updateTargets(queryIds.begin(), queryIds.begin() + min<size_t>(200, queryIds.size()));
    auto updateStart = clockType::now();
    for (int id : updateTargets) {
        auto it = find_if(inventory.begin(), inventory.end(), [id](const Barang& barang) {
            return barang.ID == id;
        });
        if (it != inventory.end()) {
            it->stok = max(0, it->stok - 1);
            it->status = getStatus(it->stok);
        }
    }
    auto updateEnd = clockType::now();

    vector<int> deleteTargets;
    size_t deleteCount = min<size_t>(120, queryIds.size());
    deleteTargets.assign(queryIds.end() - deleteCount, queryIds.end());
    auto deleteStart = clockType::now();
    for (int id : deleteTargets) {
        auto it = find_if(inventory.begin(), inventory.end(), [id](const Barang& barang) {
            return barang.ID == id;
        });
        if (it != inventory.end()) {
            inventory.erase(it);
        }
    }
    auto deleteEnd = clockType::now();

    auto toMs = [](auto durationValue) {
        return chrono::duration<double, milli>(durationValue).count();
    };

    BenchmarkResult result{};
    result.buildDuration = toMs(buildEnd - buildStart);
    result.searchDuration = toMs(searchEnd - searchStart);
    result.updateDuration = toMs(updateEnd - updateStart);
    result.deleteDuration = toMs(deleteEnd - deleteStart);
    result.searchHits = searchHits;
    result.checksum = checksum;
    result.memoryBytes = estimateVectorMemory(records);
    result.activeCount = inventory.size();
    return result;
}

BenchmarkResult runMapExperiment(const vector<Barang>& records, const vector<int>& queryIds) {
    using clockType = chrono::steady_clock;

    auto buildStart = clockType::now();
    unordered_map<int, Barang> inventory;
    for (const auto& barang : records) {
        inventory[barang.ID] = barang;
    }
    auto buildEnd = clockType::now();

    int searchHits = 0;
    long long checksum = 0;
    auto searchStart = clockType::now();
    for (int id : queryIds) {
        auto it = inventory.find(id);
        if (it != inventory.end()) {
            ++searchHits;
            checksum += static_cast<long long>(it->second.harga) * it->second.stok;
        }
    }
    auto searchEnd = clockType::now();

    vector<int> updateTargets(queryIds.begin(), queryIds.begin() + min<size_t>(200, queryIds.size()));
    auto updateStart = clockType::now();
    for (int id : updateTargets) {
        auto it = inventory.find(id);
        if (it != inventory.end()) {
            it->second.stok = max(0, it->second.stok - 1);
            it->second.status = getStatus(it->second.stok);
        }
    }
    auto updateEnd = clockType::now();

    vector<int> deleteTargets;
    size_t deleteCount = min<size_t>(120, queryIds.size());
    deleteTargets.assign(queryIds.end() - deleteCount, queryIds.end());
    auto deleteStart = clockType::now();
    for (int id : deleteTargets) {
        inventory.erase(id);
    }
    auto deleteEnd = clockType::now();

    auto toMs = [](auto durationValue) {
        return chrono::duration<double, milli>(durationValue).count();
    };

    BenchmarkResult result{};
    result.buildDuration = toMs(buildEnd - buildStart);
    result.searchDuration = toMs(searchEnd - searchStart);
    result.updateDuration = toMs(updateEnd - updateStart);
    result.deleteDuration = toMs(deleteEnd - deleteStart);
    result.searchHits = searchHits;
    result.checksum = checksum;
    result.memoryBytes = estimateMapMemory(inventory);
    result.activeCount = inventory.size();
    return result;
}

BenchmarkData buildBenchmarkData() {
    BenchmarkData data{};
    data.itemCount = 5000;
    data.queryCount = 1200;
    data.rounds = 5;

    vector<Barang> inventory = generateInventory(data.itemCount);
    data.preview.assign(inventory.begin(), inventory.begin() + min<size_t>(8, inventory.size()));
    vector<int> queryIds = createQueryIds(inventory, data.queryCount);

    vector<BenchmarkResult> vectorRounds;
    vector<BenchmarkResult> mapRounds;
    vectorRounds.reserve(data.rounds);
    mapRounds.reserve(data.rounds);

    for (int round = 0; round < data.rounds; ++round) {
        vectorRounds.push_back(runVectorExperiment(inventory, queryIds));
        mapRounds.push_back(runMapExperiment(inventory, queryIds));
    }

    auto average = [](const vector<BenchmarkResult>& rounds, auto accessor) {
        double total = 0.0;
        for (const auto& round : rounds) {
            total += accessor(round);
        }
        return total / static_cast<double>(rounds.size());
    };

    data.vectorResult.buildDuration = average(vectorRounds, [](const BenchmarkResult& round) { return round.buildDuration; });
    data.vectorResult.searchDuration = average(vectorRounds, [](const BenchmarkResult& round) { return round.searchDuration; });
    data.vectorResult.updateDuration = average(vectorRounds, [](const BenchmarkResult& round) { return round.updateDuration; });
    data.vectorResult.deleteDuration = average(vectorRounds, [](const BenchmarkResult& round) { return round.deleteDuration; });
    data.vectorResult.searchHits = vectorRounds.front().searchHits;
    data.vectorResult.checksum = vectorRounds.front().checksum;
    data.vectorResult.memoryBytes = vectorRounds.front().memoryBytes;
    data.vectorResult.activeCount = vectorRounds.front().activeCount;

    data.mapResult.buildDuration = average(mapRounds, [](const BenchmarkResult& round) { return round.buildDuration; });
    data.mapResult.searchDuration = average(mapRounds, [](const BenchmarkResult& round) { return round.searchDuration; });
    data.mapResult.updateDuration = average(mapRounds, [](const BenchmarkResult& round) { return round.updateDuration; });
    data.mapResult.deleteDuration = average(mapRounds, [](const BenchmarkResult& round) { return round.deleteDuration; });
    data.mapResult.searchHits = mapRounds.front().searchHits;
    data.mapResult.checksum = mapRounds.front().checksum;
    data.mapResult.memoryBytes = mapRounds.front().memoryBytes;
    data.mapResult.activeCount = mapRounds.front().activeCount;

    return data;
}

void writeJson(const BenchmarkData& data, const string& outputPath) {
    ofstream file(outputPath);
    if (!file.is_open()) {
        throw runtime_error("Gagal membuka file output: " + outputPath);
    }

    file << fixed << setprecision(4);
    file << "{\n";
    file << "  \"summary\": {\n";
    file << "    \"itemCount\": " << data.itemCount << ",\n";
    file << "    \"queryCount\": " << data.queryCount << ",\n";
    file << "    \"rounds\": " << data.rounds << "\n";
    file << "  },\n";

    file << "  \"preview\": [\n";
    for (size_t index = 0; index < data.preview.size(); ++index) {
        const auto& barang = data.preview[index];
        file << "    {\n";
        file << "      \"id\": \"" << barang.ID << "\",\n";
        file << "      \"nama\": \"" << jsonEscape(barang.nama) << "\",\n";
        file << "      \"stok\": " << barang.stok << ",\n";
        file << "      \"harga\": " << barang.harga << ",\n";
        file << "      \"kategori\": \"" << jsonEscape(barang.kategori) << "\",\n";
        file << "      \"status\": \"" << jsonEscape(barang.status) << "\"\n";
        file << "    }" << (index + 1 < data.preview.size() ? "," : "") << "\n";
    }
    file << "  ],\n";

    auto writeResult = [&](const string& key, const BenchmarkResult& result, bool isLast) {
        file << "  \"" << key << "\": {\n";
        file << "    \"buildDuration\": " << result.buildDuration << ",\n";
        file << "    \"searchDuration\": " << result.searchDuration << ",\n";
        file << "    \"updateDuration\": " << result.updateDuration << ",\n";
        file << "    \"deleteDuration\": " << result.deleteDuration << ",\n";
        file << "    \"searchHits\": " << result.searchHits << ",\n";
        file << "    \"checksum\": " << result.checksum << ",\n";
        file << "    \"memoryBytes\": " << result.memoryBytes << ",\n";
        file << "    \"activeCount\": " << result.activeCount << "\n";
        file << "  }" << (isLast ? "\n" : ",\n");
    };

    file << "  \"benchmark\": {\n";
    writeResult("vector", data.vectorResult, false);
    writeResult("map", data.mapResult, true);
    file << "  }\n";
    file << "}\n";
}

int main(int argc, char* argv[]) {
    try {
        string outputPath = argc > 1 ? argv[1] : string("..\\strukturData\\public\\benchmark-data.json");
        BenchmarkData data = buildBenchmarkData();
        writeJson(data, outputPath);
        cout << "Benchmark JSON ditulis ke: " << outputPath << '\n';
        return 0;
    } catch (const exception& error) {
        cerr << error.what() << '\n';
        return 1;
    }
}
