all:
	cd src;make;mv stringCount ../
upload:
	scp -r ../HW20171110 st15307110218@10.40.9.67:Homework/
download:
	scp -r st15307110218@10.40.9.67:Homework/HW20171110 ../from_server
clean:
	cd src;make clean
cleanall:
	cd src;make clean;rm ../stringCount