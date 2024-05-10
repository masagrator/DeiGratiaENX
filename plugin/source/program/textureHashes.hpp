#include <stdexcept>

struct hashTable {
	uint64_t hash;
	const char filepath[18];
};

template <typename T> constexpr bool has_duplicates(const T *array, std::size_t size)
{
	for (std::size_t i = 1; i < size; i++)
		for (std::size_t j = 0; j < i; j++)
			if (array[i].hash == array[j].hash) {
				return true;
			}
	return false;
}

constexpr hashTable TEXTURE_HASHES[] = {
	{0x5700F6042C074AC4lu, "bg/00181"},
	{0xA44762D3791FC6CDlu, "bg/00182"},
	{0x73046A7AED6F481Alu, "bg/00183"},
	{0x7D409008E72C9A51lu, "bg/00184"},
	{0x1D086086CD5BE503lu, "bg/00185"},
	{0x39EE6D6190D28FDDlu, "bg/00186"},
	{0x4F926D63E44D5255lu, "bg/00187"},
	{0xB548693D486F8845lu, "bg/00188"},
	{0x370E9CDBC5D63E48lu, "bg/00189"},
	{0x5D41C603F8702232lu, "bg/00190"},
	{0x78D5E839704BAE86lu, "bg/00191"},
	{0xBB2769519D123EFFlu, "bg/00192"},
	{0x4221C0E3B1033345lu, "bg/00193"},
	{0xDA4904D1152FD555lu, "bg/00194"},
	{0x9A21444FCE920E15lu, "bg/00195"},
	{0x38C690C366903506lu, "bg/00196"},
	{0xDB985AF8313532DDlu, "bg/00197"},
	{0x9FD2F325D7D319D0lu, "bg/00198"},
	{0xC38E27C6163191EAlu, "bg/00232"},
	{0x68DDD44A3CF061D8lu, "bg/00233"},
	{0xD447D29ACE3642ABlu, "bg/00234"},
	{0x8540D3B12B7EE666lu, "bg/00235"},
	{0xE6D9A4F9F58E3220lu, "bg/00236"},
	{0x5C7C749634E3B2ADlu, "bg/00237"},
	{0x9CCB343ADF360CE6lu, "bg/00238"},
	{0x12390F64B5E240DFlu, "bg/00239"},
	{0x722EFC5FF1A9EA2Clu, "bg/00240"},
	{0xB8C1C838B7D36C26lu, "bg/00241"},
	{0x0F80615F71FB5419lu, "bg/00242"},
	{0x1162407B97BCBEBBlu, "bg/00243"},
	{0xCDE650333190FD11lu, "bg/00244"},
	{0x57DD5BE6F633B611lu, "bg/00245"},
	{0xC23BFD9AE1A1256Blu, "bg/00246"},
	{0x09608D2C83F61F4Elu, "bg/00247"},
	{0xE42D78916BC8B8D6lu, "sys/00000/ID00000"},
	{0x9AB8DC7F8D2D42C5lu, "sys/00000/ID00016"},
	{0x601C9230161D90EBlu, "sys/00000/ID00023"},
	{0xBA48065F64D6EA27lu, "sys/00000/ID00024"},
	{0x0039AF2786A3C3B9lu, "sys/00000/ID00025"},
	{0xF1ADBCF51BBBD981lu, "sys/00000/ID00061"},
	{0x77FB6D075D950F6Alu, "sys/00000/ID00081"},
	{0x78CDE2E42CF27E74lu, "sys/00000/ID00082"},
	{0x9C8EEE9089E35AF4lu, "sys/00000/ID00083"},
	{0x5F2337EFB1454DA9lu, "sys/00000/ID00084"},
	{0x8F9FF7E62AF594F1lu, "sys/00000/ID00085"},
	{0xBC93EE3B06CAAD0Dlu, "sys/00003/ID00026"},
	{0x408E6D9370E4DD6Alu, "sys/00003/ID00027"},
	{0x9C8DE84D5205C579lu, "sys/00003/ID00028"},
	{0xD7EFAE2CC2C4AB4Flu, "sys/00006/ID00000"},
	{0x3779034953245924lu, "sys/00006/ID00007"},
	{0xBBAA31337513EB2Elu, "sys/00006/ID00011"},
	{0xCF14FB9EA1E33847lu, "sys/00006/ID00012"},
	{0xA91948E006C9B417lu, "sys/00006/ID00013"},
	{0x684E7F4EA2C49BEFlu, "sys/00006/ID00014"},
	{0x4326CC91484A4BC4lu, "sys/00006/ID00017"},
	{0x73D4F46D3A0EDDFAlu, "sys/00006/ID00018"},
	{0xA18B40087A2BC44Blu, "sys/00006/ID00019"},
	{0xF12CAB79185CFE49lu, "sys/00006/ID00020"},
	{0xCB5B384F1B19F7B3lu, "sys/00006/ID00021"},
	{0xA57A139AF7F72F5Flu, "sys/00006/ID00022"},
	{0x2020B0E4AC8ECDF8lu, "sys/00006/ID00023"},
	{0xD65196A8BBD85344lu, "sys/00006/ID00024"},
	{0x637AD90D98E7AEDClu, "sys/00006/ID00025"},
	{0x8E69AECFF9A37751lu, "sys/00006/ID00026"},
	{0xDC95B85D8862B839lu, "sys/00006/ID00031"},
	{0xC4E9E6D506301800lu, "sys/00006/ID00032"},
	{0x621E6E0778B18CB5lu, "sys/00006/ID00033"},
	{0xB56FB1BB227FC892lu, "sys/00006/ID00034"},
	{0x46A4EEF0A0A44E69lu, "sys/00006/ID00035"},
	{0xE89A9B563A14F30Flu, "sys/00006/ID00036"},
	{0x373D2D8107ED3EF7lu, "sys/00006/ID00039"},
	{0x342B5F751F52E6D4lu, "sys/00006/ID00040"},
	{0x5A35B6F6343A87DFlu, "sys/00006/ID00041"},
	{0x8DE86BF3DA1638F8lu, "sys/00006/ID00042"},
	{0x3DCBC6F2F4ECE142lu, "sys/00006/ID00043"},
	{0xD3BA0CACCD2567BElu, "sys/00006/ID00044"},
	{0xD437AD28CDED19D4lu, "sys/00006/ID00045"},
	{0x9ADD8B4024730A83lu, "sys/00006/ID00046"},
	{0xE0B6D19E7940342Flu, "sys/00006/ID00047"},
	{0xF29930641E8E3120lu, "sys/00006/ID00048"},
	{0x714FB06F84B258C5lu, "sys/00006/ID00049"},
	{0x384E35C6A201791Elu, "sys/00006/ID00050"},
	{0xF4C71FD0361FE5CFlu, "sys/00007/ID00000"},
	{0x92CC70B7E341AEEDlu, "sys/00007/ID00001"},
	{0x032E9BF2F14A206Clu, "sys/00009/ID00000"}
};

static_assert(!has_duplicates(TEXTURE_HASHES, std::size(TEXTURE_HASHES)), "Detected repeated hash!");

const char* compareHashes(uint64_t hashToCompare) {
	for(size_t i = 0; i < std::size(TEXTURE_HASHES); i++)
		if (TEXTURE_HASHES[i].hash == hashToCompare) 
			return TEXTURE_HASHES[i].filepath;
	return nullptr;
}