; ModuleID = 'llvm-link'
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.11.0"

@.str = private unnamed_addr constant [96 x i8] c"clang++-3.8 -O3 -Wall -Iinclude -std=c++11 -o betmidi src-programs/betmidi.cpp -Llib -lmidifile\00", align 1
@.str.1 = private unnamed_addr constant [10 x i8] c"./betmidi\00", align 1

; Function Attrs: norecurse ssp uwtable
define i32 @main() #0 {
entry:
  call void @_Z8call_exev()
  ret i32 0
}

; Function Attrs: ssp uwtable
define void @_Z8call_exev() #1 {
entry:
  %call = call i32 @"\01_system"(i8* getelementptr inbounds ([96 x i8], [96 x i8]* @.str, i32 0, i32 0))
  %call1 = call i32 @"\01_system"(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.1, i32 0, i32 0))
  ret void
}

declare i32 @"\01_system"(i8*) #2

attributes #0 = { norecurse ssp uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+ssse3" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { ssp uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+ssse3" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+ssse3" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0, !0}
!llvm.module.flags = !{!1}

!0 = !{!"clang version 3.8.1 (tags/RELEASE_381/final)"}
!1 = !{i32 1, !"PIC Level", i32 2}
