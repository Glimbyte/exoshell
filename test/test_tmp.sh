echo test.sh

assert() {
  # テストしようとしている内容をprint
	printf '%-30s:' "\"$1\""

	# bashの出力をcmpに保存
	echo -n -e "$1" | bash >bash_histry 2>&-
	# bashのexit statusをexpectedに代入
	expected=$?
	# minishellの出力をoutに保存
	echo -n -e "$1" | ../minishell >shell_histry 2>&-
	# minishellのexit statusをactualに代入
	actual=$?

	# bashとminishellの出力を比較
	diff bash_histry bash_histry >/dev/null && echo -n '  diff OK' || echo -n '  diff NG'

	# bashとminishellのexit statusを比較
	if [ "$actual" = "$expected" ]; then
		echo -n '  status OK'
	else
		echo -n "  status NG, expected $expected but got $actual"
	fi
	echo
}

# Empty line (EOF)
assert ''
assert '/bin/pwd'
assert '/bin/echo'
assert '/bin/ls'
