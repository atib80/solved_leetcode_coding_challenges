/*
567. Leetcode coding challenge: Permutation in string

Given two strings s1 and s2, write a function to return true if s2 contains the
permutation of s1. In other words, one of the first string's permutations is the
substring of the second string.

Example 1:

Input:  s1 = "ab" s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").

Example 2:

Input:  s1= "ab" s2 = "eidboaoo"
Output: false

Note:

    The input strings only contain lower case letters.
    The length of both given strings is in range [1, 10,000].

*/

#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  bool check_if_src_contains_permutation_of_needle(
      const string& src,
      const size_t src_len,
      const string& needle,
      const size_t needle_len,
      string& dst_str,
      vector<int>& visited_indices,
      unordered_set<string>& already_visited_needles,
      int& end_search) {
    for (size_t i{}; !end_search && i < needle_len; i++) {
      if (visited_indices[i])
        continue;

      visited_indices[i] = 1;
      dst_str.push_back(needle[i]);

      const size_t s2_needle_offset{src.find(dst_str)};

      if (string::npos == s2_needle_offset) {
        if (1 == dst_str.size()) {
          end_search = 1;
          return false;
        }
        already_visited_needles.insert(dst_str);
        dst_str.pop_back();
        visited_indices[i] = 0;
        continue;
      }

      if (dst_str.length() == needle_len)
        return true;

      if (s2_needle_offset + needle_len <= src_len &&
          !already_visited_needles.count(dst_str)) {
        already_visited_needles.insert(dst_str);
        if (check_if_src_contains_permutation_of_needle(
                src, src_len, needle, needle_len, dst_str, visited_indices,
                already_visited_needles, end_search))
          return true;
      }

      dst_str.pop_back();
      visited_indices[i] = 0;
    }

    return false;
  }

 public:
  bool checkInclusion(string& s1, const string& s2) {
    const size_t s1_len{s1.length()};
    const size_t s2_len{s2.length()};
    if (s1_len > s2_len)
      return false;
    if (string::npos != s2.find(s1))
      return true;

    string dst_str{};
    dst_str.reserve(s1_len);
    vector<int> visited_indices(s1_len, 0);
    unordered_set<string> already_visited_needles{};
    int end_search{};

    const bool is_permutation_of_s1_contained_in_s2{
        check_if_src_contains_permutation_of_needle(
            s2, s2_len, s1, s1_len, dst_str, visited_indices,
            already_visited_needles, end_search)};

    return is_permutation_of_s1_contained_in_s2;
  }
};

int main() {
  Solution s{};
  string s1{"ab"};
  cout << boolalpha << "s.checkInclusion(\"ab\", \"eidbaooo\") -> "
       << s.checkInclusion(s1, "eidbaooo") << '\n';  // expected output: true
  cout << "s.checkInclusion(\"ab\", \"eidboaoo\") -> "
       << s.checkInclusion(s1, "eidboaoo") << '\n';  // expected output: false
  s1 = "trinitrophenylmethylnitramine";
  cout << "s.checkInclusion(\"trinitrophenylmethylnitramine\", "
          "\"dinitrophenylhydrazinetrinitrophenylmethylnitramine\") -> "
       << s.checkInclusion(
              s1, "dinitrophenylhydrazinetrinitrophenylmethylnitramine")
       << '\n';  // expected output: true
  s1 = "adc";
  cout << "s.checkInclusion(\"adc\", "
          "\"dcda\") -> "
       << s.checkInclusion(s1, "dcda") << '\n';  // expected output: true

  s1 = "kuzntqeuvaszrspkgjvxrupwxwrexztptsowceibeewxbslvosbobmyymikdscshybtmanu"
       "xeqtanrjekbwirmhgvfmzipfiqxcilarfyasoayepgfzmdytlpjymeaztsyubkbmblepwoz"
       "ffxiitdhwaquozlfmnascomqczrbhxcnzugppddtudxrigfeaozzojpeamnobapgwksudbi"
       "wdedvprwonmzardsodhxmkgghqzfhorjaijdvwzsnfpdfklwibbsnwqsoajcpjisbgizgtt"
       "lnmclawbgnhbmtcpuusuammvgxnopdngclxumgfgwjrinamevhirpmlkwtyxkrmoffrreot"
       "dosjghsrkgxyiyrytbbofgczndgmdalyvvoljczcztxitxelywqemjigtuanubpstndwzvt"
       "iejtoqvetaehvcuujyupncumjnkesmoadzyvkwvjqgqewvvvpheyyvkewefbjjqzajxnhou"
       "odanyruqpzdcjmgnxkmhsgqjhpcyviewmrkfioudzqivmmguxjxuxdmpsmkwnvbxcomifgx"
       "qmcovlkooptjpfxjllwtlkkoaayzduodgsusaogswmoqkznynwiukkrrxzkwcknwlazxnlm"
       "ghybxmyvquzbdqlpfydhnnuvlmyjmixyzso";
  cout << "s.checkInclusion("
          "\"kuzntqeuvaszrspkgjvxrupwxwrexztptsowceibeewxbslvosbobmyymikdscshyb"
          "tmanuxeqtanrjekbwirmhgvfmzipfiqxcilarfyasoayepgfzmdytlpjymeaztsyubkb"
          "mblepwozffxiitdhwaquozlfmnascomqczrbhxcnzugppddtudxrigfeaozzojpeamno"
          "bapgwksudbiwdedvprwonmzardsodhxmkgghqzfhorjaijdvwzsnfpdfklwibbsnwqso"
          "ajcpjisbgizgttlnmclawbgnhbmtcpuusuammvgxnopdngclxumgfgwjrinamevhirpm"
          "lkwtyxkrmoffrreotdosjghsrkgxyiyrytbbofgczndgmdalyvvoljczcztxitxelywq"
          "emjigtuanubpstndwzvtiejtoqvetaehvcuujyupncumjnkesmoadzyvkwvjqgqewvvv"
          "pheyyvkewefbjjqzajxnhouodanyruqpzdcjmgnxkmhsgqjhpcyviewmrkfioudzqivm"
          "mguxjxuxdmpsmkwnvbxcomifgxqmcovlkooptjpfxjllwtlkkoaayzduodgsusaogswm"
          "oqkznynwiukkrrxzkwcknwlazxnlmghybxmyvquzbdqlpfydhnnuvlmyjmixyzso\","
          "\"zthosfejqodcstlqczkndmgwtcakxzxaklkrehkfwnokclametzpnblcwaspdblfoo"
          "psiqrpzlbmlysddlqxcjzezcpknwzljvhmqxqinmptcppipifchxexlytleambzwmqwg"
          "vxlehnecdqsqbrxqfwvcovgdvtmwbnvajvkizixbmuiuyuixjhiohimghdbohetogrhz"
          "sbzgpekosxcjglsrvzenovpjyzknuumpsdrufcjsyfbuwfmaaztxjbpjctnuwcqknnem"
          "ptjbgfthyafeatskfmysaioqikcpywmefujnvthumyhareltknxyvqprexgbwyzodfki"
          "nltwobeukrmpyjkrgvwhbtnzaozgxouxndmkyvzlujhxxwebptykctbojgnvcwhhgsyo"
          "hccrqxksdyygcwdsazlznhqjdddisjmfqvjqcquuvjrzkcvzpxpfakbkrqlzacanqbgg"
          "avezedqmoffxmkrlcwxdeosvhvvknqimwpasrlldewvhppzixgcxisysgeppcwfknecu"
          "pyrrqnkhvessintrequaqiuoesgyndovaqxnlldmdupjcjzejannfjfasguyvgsdakwx"
          "ezrginhdstbrtqmznpkasytqtbfyftwhgnuazcwehsvcdukuifmkefzabxyhihgnldps"
          "vglubalbsvqstfxehvnpxmrejnkqacafuvzghbttgqmjhqzejasoasbpjirfawcvwahy"
          "kvrfpaadcgvxssebdznzyvamyilahahgdslwvpuvzsinbbqecdqyvwnucjzyxmxwqwyx"
          "bxoljnjcqqdumghmcvqpcpjlxemupospxvkicqvyiavatbojgzurfzitgpeqjmvsgzzq"
          "phciyweyavebslgegjcyqmgehchryyclswjequeijzpsvuercqzhwgtgyxhxavhqkrwq"
          "dvkqvklicxpasnsnbgybtufdgbwrpaewzwczabckvddtewunsktcznqkivsubdjrpzxt"
          "sohiilcybrwqtlfqmjzmvpbfjmbjvbpwietkyzwzizwuiohjuhoekejhmkrooeyydmav"
          "dencmxhsxdnyitzivlymzyqogdhzrwhbdupborzqihurziajjwbrfwkzgbpmfgtobkbz"
          "yijcgkszyuyouyxvztmmtaqetcaxqrkbrmkzyokglckifgdfidjqoiqrfrpftagxxoqo"
          "dbyygdioxdznycssxjvpotsrptttrbjayhugecptuibezsyggqcyvzosvmlpwmnuhovv"
          "hfyazkdrfxlxjxpbkkbuexxnklhnkteyjshhlojnbxtyltdfzhulcsptinpsskaeowof"
          "ruejqpinhivlpvvosppxtbbrebvfihmamdlvsjirwfzhzmaqzuryakjlzroxrlwccdan"
          "nvzwenabvosplnwhotxyzxhocdnvsekmnepzzqjhqrokocqewpihhyftshsfehijlvpa"
          "jrcrgeqqjigmzkrhcgafqkdkrkkyausijdfzqewawxurtzhioqqnoxhbrdrriveapdeb"
          "bwbrnmpcakomfhpfrqvzmpqkqucoepjklaqtirgkcrgpdhvyxybnulrchqgbupjdxxal"
          "bwljfpdjfnlqfquhdxvvuaecgzgfhulhkkvpuexpssodxqxhrbpzzgdiohxzjxnuhtav"
          "littooxkuededfxdaabuzdlwjhitwykqdvtrwuohpvpgpeudhpslpvxmotibojtgvohq"
          "aaowiofdtgbkiiurhcfavlgsnqxndcxyxozklduxqeovzrtwuhoikgpyqoqwllagzufk"
          "uzntqeuvaszrspkgjvxrupwxwrexztptsowceibeewxbslvosbobmyymikdscshybtma"
          "nuxeqtanrjekbwirmhgvfmzipfiqxcilarfyfsoayepgfzmdytlpjymeaztsyubkbmbl"
          "epwozffxiitdhwaquozlfmnascomqczrbhxcnzugppddtudxrigfeaozzojpeamnobap"
          "gwksudbmwdedvprwonmzardsodhxmkgghqzfhorjaijdvwzsnfpdfklwibbsnwqsoajc"
          "pjisbgizgttlnmclawbgnhbmtcpuusuamivgxnopdngclxumgfgwjrinamevhirpmlkw"
          "tyxkrmoafrreotdosjghsrkgxyiyrytbbofgczndgmdalyvvoljczcztxitxelywqemj"
          "igtuanubpstndwzvtiejtoqvetaehvcuujyupncumjnkesmoadzyvkwvjqgqewvvvphe"
          "yyvkewefbjjqzajxnhouodanyruqpzdcjmgnxkmhsgqjhpcyviewmrkfioudzqivmmgu"
          "xjxuxdmpsmkwnvbxcomifgxqmcovlkooptjpfxjllwtlkkoaayzduodgsusaogswmoqk"
          "znynyiukkrrxzkwcknwlazxnlmghybxmyvquzbdqlpfydhnnuvlmyjmixwzsoufvjlrq"
          "tzxvybzhurdqdtnkciiradptqxzgrkqgfbnsmptyyggwpenatlrtpvmdpveivmenzwjl"
          "wdhlhmmpvbglhxcinvhhcphgklicwwnwqbkbndiuqowwgzdczwvlazndbboublzrltxa"
          "hxenivmkbwofrnkkvjixfbbctshvqzmgwqrmheupodlrnebsidrbxxjfeoqgcoscymzs"
          "kvbamtxtpumbdmedjghxazwamkqdrxsqytqxkrrqcnwrtkuaocuwmyucctdnaqfjloso"
          "vveoxjyypqrbkflxrrxlnjxhkrrvjettqfzzbwbzowsufxmppazhwiwcvimmlixdzgpm"
          "fayrblbkulfopwarxlsbfkuqvhyufwdswfpxqwhuvepyslbliapotofrxhufoopqhqjc"
          "jdtleeoedsacpeqfewxehghwvfvqmlzvzudkqxinsfekpbaggbpohbtbhcvdzvuormpz"
          "adkhhqqyspfkijjcelofwgkgimjxrkwqwhpqfihyhmwdkwhathcxvxtuopufsjaagbam"
          "ghtsjewrpooxrprtvqpslsbaijrzojgwhekijtfugwbvgdltgpentcyjbwqjcdqkhicb"
          "sdvgtvsecpsacesztkjdskoumcheqzmoijoimnmnhfavttfamkkvugpmnibdzhcieyhh"
          "ctifhbvqrllslpvymjamfmgladmpeqdrtumbqwcwwkduavjokhjrdbdozxaqemvurjwd"
          "ukuwrbzfstuesjqfgblvvaqemylqgrtfzdrfgtcbvaokygyidfsbppasppzcunjwbrhq"
          "scumnrugeyxqvceninwsvmqcekvuetloevkrntgsrivpebgoobcggmgwkrzagkdavpej"
          "dgkpokcdpvncsmduzhowhdjklqwyphevtaugcabxovxgjovvgzksukpnadsblbpnuuih"
          "xdkovwsmniptwhrjxhyitozdwgkdkasspklxbyfmmugmawjflmrdiqmolsufpyzkrrqr"
          "vgnbtcogomdjrymxgnocnmpsdmbncterfrrxqyrsdqjzrodttnjbblleexyvfzxemlxf"
          "mxbzffflpyifrqhbdnwpuuwfhskfevjshsxvhvbldqyxenpxkvamashnbmrfiladqnuz"
          "wltrkoegwxrjveajpyvchyotakniwcyigejnaspdfjssacnfhbyobgrovavxoclvkgvg"
          "ivoiycquftjuqynabeqakugedwlogqfbbivbzisljreuowaxfaugjunbyrcxvlqjvvue"
          "wgprwfiofxyzdaomzjfystxrbpmgdwyznnuzibozcjtsxxastlhmjpogvuhdtfhnmrhd"
          "xihhrtxqocmsmysxuudsdquadshqncpbejkjarbhkwkstpcqgwuarnmvtfjvdzeeklwn"
          "njdewmwdyzdfnryaqoiysysfvlxetggjhywxwvkvvuccklxptokzvrrhodicekjrffbd"
          "jxoftxbstcbxjcksqcvcwkisywdzepzgznaorlllmahrqepouqnrtbhgxnsnyhkacxhj"
          "zgvxhlukbvspfzqgguqkngncotvgvuygijtkucvqcsjjolodnbfeznuikkaghyyqtxmt"
          "djchrgybirzkbysbgnwwqaxjsnneazxnmdyzooizcyqtxlmqvujoqhjqlnuvojlkcdyb"
          "fryidsunirmymtvltnjiggwxeqowcnbukotbngjaidyvhmobdxlklwqxshkaphxwdxzo"
          "nqddvstwrrtatklpujldtgrofxyunlmlwquruzekmdymzhpuuuaiyinmaedxxhhayzyb"
          "sepcohcrymkysdaeagmhodvkoissnegjecmtnbydbakamurdqwwgqqfbefltdkdvyldj"
          "xynweicudbwirebvzknodfkycidoqaalxorwlvnosvcpudvsiljwlmfqpvwtbjeyydex"
          "vfmkiilwlxcpnogyeyspjaumcbrgxkeeezgyrbmtkotoyjnedraupxevwjcluyxdctfa"
          "zusyqeklxpotczvkphllcgfrykpuwscfknqhfkxdihdkymiqizppipnbflfhduzjgvoe"
          "hhvtqolybcshofasguaaeaakcsxqsqxpuydzhndleoxgmkrtlivudapfhefocneliicm"
          "rtishcmxmcdskyedbqppswqnesziwankobhaxklswulygdojhpobyezjzyengtfulymy"
          "bqiodmkirqpggycyouzqhrexnntvnlhhokdyzvudgilvqpjkeactaivsjdwfesruusew"
          "lpscumpqslulwrhramanthuogjdadmqjeccbutdfexdcsbqujpqdlryelnzvfbncraji"
          "cdnomidvmspjljjzglnahdmrctedjzdtozllmmyeamctrcyrzzdzwvfqgjfstbtitgme"
          "ogjpgllpihylxgupxxqmheusrglbampwrhtejoqqjkcljmppmemguapopatjkbzomweg"
          "krwxblxgymfmurhfokjkhljtxosxtgmaldrjjhxrcvuddvzlamavxpzszsrfepfsukad"
          "tnwyzhwdergrofmetngzuifiuonziduvucichmxhmxrulpykwedymiycbhcsvrkctvqq"
          "fvygtlyhlqbrwvmbgnwlryeotjkvowxmdlyjhyvtvyognldmsxqlotfzvxrmdultwbsn"
          "stmjakjaqqpfurvwturqyzcnfkoxumuquwgpersslowdvrnssqcgwmfnssvtobdwcsco"
          "ikoythwhsxswsmsimntribaohzrmjculdnnguchmqgyzqeipuumwgizlvjmpvyotgzmt"
          "santswdarbyaklpiclafgqdaoeiitxlcpwhlqsidkb\") -> "
       << s.checkInclusion(
              s1,
              "zthosfejqodcstlqczkndmgwtcakxzxaklkrehkfwnokclametzpnblcwaspdblf"
              "oopsiqrpzlbmlysddlqxcjzezcpknwzljvhmqxqinmptcppipifchxexlytleamb"
              "zwmqwgvxlehnecdqsqbrxqfwvcovgdvtmwbnvajvkizixbmuiuyuixjhiohimghd"
              "bohetogrhzsbzgpekosxcjglsrvzenovpjyzknuumpsdrufcjsyfbuwfmaaztxjb"
              "pjctnuwcqknnemptjbgfthyafeatskfmysaioqikcpywmefujnvthumyhareltkn"
              "xyvqprexgbwyzodfkinltwobeukrmpyjkrgvwhbtnzaozgxouxndmkyvzlujhxxw"
              "ebptykctbojgnvcwhhgsyohccrqxksdyygcwdsazlznhqjdddisjmfqvjqcquuvj"
              "rzkcvzpxpfakbkrqlzacanqbggavezedqmoffxmkrlcwxdeosvhvvknqimwpasrl"
              "ldewvhppzixgcxisysgeppcwfknecupyrrqnkhvessintrequaqiuoesgyndovaq"
              "xnlldmdupjcjzejannfjfasguyvgsdakwxezrginhdstbrtqmznpkasytqtbfyft"
              "whgnuazcwehsvcdukuifmkefzabxyhihgnldpsvglubalbsvqstfxehvnpxmrejn"
              "kqacafuvzghbttgqmjhqzejasoasbpjirfawcvwahykvrfpaadcgvxssebdznzyv"
              "amyilahahgdslwvpuvzsinbbqecdqyvwnucjzyxmxwqwyxbxoljnjcqqdumghmcv"
              "qpcpjlxemupospxvkicqvyiavatbojgzurfzitgpeqjmvsgzzqphciyweyavebsl"
              "gegjcyqmgehchryyclswjequeijzpsvuercqzhwgtgyxhxavhqkrwqdvkqvklicx"
              "pasnsnbgybtufdgbwrpaewzwczabckvddtewunsktcznqkivsubdjrpzxtsohiil"
              "cybrwqtlfqmjzmvpbfjmbjvbpwietkyzwzizwuiohjuhoekejhmkrooeyydmavde"
              "ncmxhsxdnyitzivlymzyqogdhzrwhbdupborzqihurziajjwbrfwkzgbpmfgtobk"
              "bzyijcgkszyuyouyxvztmmtaqetcaxqrkbrmkzyokglckifgdfidjqoiqrfrpfta"
              "gxxoqodbyygdioxdznycssxjvpotsrptttrbjayhugecptuibezsyggqcyvzosvm"
              "lpwmnuhovvhfyazkdrfxlxjxpbkkbuexxnklhnkteyjshhlojnbxtyltdfzhulcs"
              "ptinpsskaeowofruejqpinhivlpvvosppxtbbrebvfihmamdlvsjirwfzhzmaqzu"
              "ryakjlzroxrlwccdannvzwenabvosplnwhotxyzxhocdnvsekmnepzzqjhqrokoc"
              "qewpihhyftshsfehijlvpajrcrgeqqjigmzkrhcgafqkdkrkkyausijdfzqewawx"
              "urtzhioqqnoxhbrdrriveapdebbwbrnmpcakomfhpfrqvzmpqkqucoepjklaqtir"
              "gkcrgpdhvyxybnulrchqgbupjdxxalbwljfpdjfnlqfquhdxvvuaecgzgfhulhkk"
              "vpuexpssodxqxhrbpzzgdiohxzjxnuhtavlittooxkuededfxdaabuzdlwjhitwy"
              "kqdvtrwuohpvpgpeudhpslpvxmotibojtgvohqaaowiofdtgbkiiurhcfavlgsnq"
              "xndcxyxozklduxqeovzrtwuhoikgpyqoqwllagzufkuzntqeuvaszrspkgjvxrup"
              "wxwrexztptsowceibeewxbslvosbobmyymikdscshybtmanuxeqtanrjekbwirmh"
              "gvfmzipfiqxcilarfyfsoayepgfzmdytlpjymeaztsyubkbmblepwozffxiitdhw"
              "aquozlfmnascomqczrbhxcnzugppddtudxrigfeaozzojpeamnobapgwksudbmwd"
              "edvprwonmzardsodhxmkgghqzfhorjaijdvwzsnfpdfklwibbsnwqsoajcpjisbg"
              "izgttlnmclawbgnhbmtcpuusuamivgxnopdngclxumgfgwjrinamevhirpmlkwty"
              "xkrmoafrreotdosjghsrkgxyiyrytbbofgczndgmdalyvvoljczcztxitxelywqe"
              "mjigtuanubpstndwzvtiejtoqvetaehvcuujyupncumjnkesmoadzyvkwvjqgqew"
              "vvvpheyyvkewefbjjqzajxnhouodanyruqpzdcjmgnxkmhsgqjhpcyviewmrkfio"
              "udzqivmmguxjxuxdmpsmkwnvbxcomifgxqmcovlkooptjpfxjllwtlkkoaayzduo"
              "dgsusaogswmoqkznynyiukkrrxzkwcknwlazxnlmghybxmyvquzbdqlpfydhnnuv"
              "lmyjmixwzsoufvjlrqtzxvybzhurdqdtnkciiradptqxzgrkqgfbnsmptyyggwpe"
              "natlrtpvmdpveivmenzwjlwdhlhmmpvbglhxcinvhhcphgklicwwnwqbkbndiuqo"
              "wwgzdczwvlazndbboublzrltxahxenivmkbwofrnkkvjixfbbctshvqzmgwqrmhe"
              "upodlrnebsidrbxxjfeoqgcoscymzskvbamtxtpumbdmedjghxazwamkqdrxsqyt"
              "qxkrrqcnwrtkuaocuwmyucctdnaqfjlosovveoxjyypqrbkflxrrxlnjxhkrrvje"
              "ttqfzzbwbzowsufxmppazhwiwcvimmlixdzgpmfayrblbkulfopwarxlsbfkuqvh"
              "yufwdswfpxqwhuvepyslbliapotofrxhufoopqhqjcjdtleeoedsacpeqfewxehg"
              "hwvfvqmlzvzudkqxinsfekpbaggbpohbtbhcvdzvuormpzadkhhqqyspfkijjcel"
              "ofwgkgimjxrkwqwhpqfihyhmwdkwhathcxvxtuopufsjaagbamghtsjewrpooxrp"
              "rtvqpslsbaijrzojgwhekijtfugwbvgdltgpentcyjbwqjcdqkhicbsdvgtvsecp"
              "sacesztkjdskoumcheqzmoijoimnmnhfavttfamkkvugpmnibdzhcieyhhctifhb"
              "vqrllslpvymjamfmgladmpeqdrtumbqwcwwkduavjokhjrdbdozxaqemvurjwduk"
              "uwrbzfstuesjqfgblvvaqemylqgrtfzdrfgtcbvaokygyidfsbppasppzcunjwbr"
              "hqscumnrugeyxqvceninwsvmqcekvuetloevkrntgsrivpebgoobcggmgwkrzagk"
              "davpejdgkpokcdpvncsmduzhowhdjklqwyphevtaugcabxovxgjovvgzksukpnad"
              "sblbpnuuihxdkovwsmniptwhrjxhyitozdwgkdkasspklxbyfmmugmawjflmrdiq"
              "molsufpyzkrrqrvgnbtcogomdjrymxgnocnmpsdmbncterfrrxqyrsdqjzrodttn"
              "jbblleexyvfzxemlxfmxbzffflpyifrqhbdnwpuuwfhskfevjshsxvhvbldqyxen"
              "pxkvamashnbmrfiladqnuzwltrkoegwxrjveajpyvchyotakniwcyigejnaspdfj"
              "ssacnfhbyobgrovavxoclvkgvgivoiycquftjuqynabeqakugedwlogqfbbivbzi"
              "sljreuowaxfaugjunbyrcxvlqjvvuewgprwfiofxyzdaomzjfystxrbpmgdwyznn"
              "uzibozcjtsxxastlhmjpogvuhdtfhnmrhdxihhrtxqocmsmysxuudsdquadshqnc"
              "pbejkjarbhkwkstpcqgwuarnmvtfjvdzeeklwnnjdewmwdyzdfnryaqoiysysfvl"
              "xetggjhywxwvkvvuccklxptokzvrrhodicekjrffbdjxoftxbstcbxjcksqcvcwk"
              "isywdzepzgznaorlllmahrqepouqnrtbhgxnsnyhkacxhjzgvxhlukbvspfzqggu"
              "qkngncotvgvuygijtkucvqcsjjolodnbfeznuikkaghyyqtxmtdjchrgybirzkby"
              "sbgnwwqaxjsnneazxnmdyzooizcyqtxlmqvujoqhjqlnuvojlkcdybfryidsunir"
              "mymtvltnjiggwxeqowcnbukotbngjaidyvhmobdxlklwqxshkaphxwdxzonqddvs"
              "twrrtatklpujldtgrofxyunlmlwquruzekmdymzhpuuuaiyinmaedxxhhayzybse"
              "pcohcrymkysdaeagmhodvkoissnegjecmtnbydbakamurdqwwgqqfbefltdkdvyl"
              "djxynweicudbwirebvzknodfkycidoqaalxorwlvnosvcpudvsiljwlmfqpvwtbj"
              "eyydexvfmkiilwlxcpnogyeyspjaumcbrgxkeeezgyrbmtkotoyjnedraupxevwj"
              "cluyxdctfazusyqeklxpotczvkphllcgfrykpuwscfknqhfkxdihdkymiqizppip"
              "nbflfhduzjgvoehhvtqolybcshofasguaaeaakcsxqsqxpuydzhndleoxgmkrtli"
              "vudapfhefocneliicmrtishcmxmcdskyedbqppswqnesziwankobhaxklswulygd"
              "ojhpobyezjzyengtfulymybqiodmkirqpggycyouzqhrexnntvnlhhokdyzvudgi"
              "lvqpjkeactaivsjdwfesruusewlpscumpqslulwrhramanthuogjdadmqjeccbut"
              "dfexdcsbqujpqdlryelnzvfbncrajicdnomidvmspjljjzglnahdmrctedjzdtoz"
              "llmmyeamctrcyrzzdzwvfqgjfstbtitgmeogjpgllpihylxgupxxqmheusrglbam"
              "pwrhtejoqqjkcljmppmemguapopatjkbzomwegkrwxblxgymfmurhfokjkhljtxo"
              "sxtgmaldrjjhxrcvuddvzlamavxpzszsrfepfsukadtnwyzhwdergrofmetngzui"
              "fiuonziduvucichmxhmxrulpykwedymiycbhcsvrkctvqqfvygtlyhlqbrwvmbgn"
              "wlryeotjkvowxmdlyjhyvtvyognldmsxqlotfzvxrmdultwbsnstmjakjaqqpfur"
              "vwturqyzcnfkoxumuquwgpersslowdvrnssqcgwmfnssvtobdwcscoikoythwhsx"
              "swsmsimntribaohzrmjculdnnguchmqgyzqeipuumwgizlvjmpvyotgzmtsantsw"
              "darbyaklpiclafgqdaoeiitxlcpwhlqsidkb")
       << '\n';  // expected output: true

  s1 = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrs"
       "tuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkl"
       "mnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcde"
       "fghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwx"
       "yzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopq"
       "rstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghij"
       "klmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabc"
       "def";
  cout << "s.checkInclusion("
          "\"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmn"
          "opqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd"
          "efghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrst"
          "uvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghij"
          "klmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
          "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnop"
          "qrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdef"
          "ghijklmnopqrstuvwxyzabcdef\", "
          "\"bcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmno"
          "pqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcde"
          "fghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstu"
          "vwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijk"
          "lmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyza"
          "bcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopq"
          "rstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefg"
          "hijklmnopqrstuvwxyzabcdefg\") -> "
       << s.checkInclusion(
              s1,
              "bcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklm"
              "nopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxy"
              "zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijk"
              "lmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvw"
              "xyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghi"
              "jklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstu"
              "vwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefg"
              "hijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefg")
       << '\n';  // expected output: true

  return 0;
}
