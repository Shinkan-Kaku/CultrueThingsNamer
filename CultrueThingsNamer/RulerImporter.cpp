#include "QString";
#include "QList";
class RuleImporter
{
	public:
		RuleImporter()
		{

		}
		/*
		 * 舊方法群，內容主要是將受委託的rule文件掃描，將內容記成ArrayList並回傳
		 */
		static QList<QString> openRulefileWithSingleLin(QString Address)
		{

		}
		static QList<QString> openRulefilesWithMutilLines(QString folder,QString Address)
		{

		}
		//方法2,區別在於將掃描文件輸出內容 從 字串清單 改成 "新格式"物件清單
		static QList<QString> makeRulesWithMutilLinesToRuledats(QString folder)
		{

		}
		static QList<QString> getOnlyFoldersName(QString targetDirection)
		{

		}
		static QList<QString> getTargetFolderFileList(QString Address)
		{

		}
};