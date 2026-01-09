#pragma once

#include "../n520_evaluate/n520_400_KkKkpKppStorageBase.hpp"


/// <summary>
/// ［玉］［その他の駒１］［その他の駒２］キャッシュ入出力☆
/// </summary>
class KppCacheIo {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="dirName"></param>
	/// <param name="k1"></param>
	/// <returns></returns>
	std::string GetLv2FilePath(const std::string& dirName, int k1);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="dirName"></param>
	/// <param name="k1"></param>
	/// <param name="p1"></param>
	/// <returns></returns>
	std::string GetLv3FilePath(const std::string& dirName, int k1, int p1);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="dirName"></param>
	/// <param name="k1"></param>
	/// <returns></returns>
	bool SynthesizeLv3To2(const std::string& dirName, int k1);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="dirName"></param>
	/// <param name="k1"></param>
	/// <param name="p1"></param>
	/// <param name="kppArray"></param>
	/// <returns></returns>
	bool WriteLv3Files(const std::string& dirName, int k1, int p1, std::array<s16, 2> kppArray[SquareNum][fe_end][fe_end]);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="cache3Filepath"></param>
	/// <param name="k1"></param>
	/// <param name="p1"></param>
	/// <param name="kppArray"></param>
	void WriteLv3FilesBody(const std::string& cache3Filepath, int k1, int p1, std::array<s16, 2> kppArray[SquareNum][fe_end][fe_end]);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="dirName"></param>
	/// <param name="k1"></param>
	/// <param name="kppArray"></param>
	/// <returns></returns>
	bool ReadLv2Files(const std::string& dirName, int k1, std::array<s16, 2> kppArray[SquareNum][fe_end][fe_end]);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="dirName"></param>
	/// <param name="k1"></param>
	/// <param name="p1"></param>
	/// <param name="kppArray"></param>
	/// <returns></returns>
	bool ReadLv3Files(const std::string& dirName, int k1, int p1, std::array<s16, 2> kppArray[SquareNum][fe_end][fe_end]);
};
