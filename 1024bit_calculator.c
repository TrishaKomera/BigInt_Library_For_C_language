#include<stdio.h>
/*BT21CSE051_CPL_Assignment_2.c*/
typedef struct bigint//defining the structure Bigint
{//As we are implementing 1024 bit arithmetic operations we need to see max how many digits can be there. For that we need to equate 2^1024 = 10^p
    char str[310];//log(2^1024)=p =>p= 308.2547155599 =>so 2^1024 will have step(308.2547155599)+1=309
    int length;//length of the string
}bigint;
void bigintinitialize(bigint *bg,int l1, int l2)//Initializing with 0's in the multiplication
{
    bg->length=l1+l2;//max number in c1 is 10^l1-1 and in c2 is 10^l2-1,So max number in ans=(10^l1-1)( 10^l2-1)
    int i=0;//so the max number of digits is l1+l2
    while(i<l1+l2)
    {
        bg->str[i]='0';
        i++;
    }
}
bigint bigintscan(bigint p)//scanning the string of the bigint
{
    char ch;
    scanf("%c", &ch);
	int i = 0,flag=0;
	while(ch != '\n'&& ch != '\t'&&flag==0)
	{
		if(ch>='0'&&ch<='9')
        {
            p.str[i] = ch;
		    scanf("%c", &ch);
		    i++;
        }
        else
        {
            flag=1;//when other 0 to 9 characters are entered 
        }
	}
    if(flag==0)
    {
        p.length=i;
        p.str[i]='\0';
    }
    else//error case
    {
        printf("The number should range from 0 to 9 only\n");
        printf("Please enter the number properly from the start\n");
        printf("Enter the number again :");
    }
    return p;
}
void bigintaddition(bigint c1,bigint c2)//Addition of the 2 strings
{
    bigint ans;
    int p=(c1.length>c2.length)?c1.length:c2.length;//storing max length as max length of c1.len,c2.len
    int carry=0,sum;//Initially carry=0;
    int s1=c1.length,s2=c2.length;
    ans.str[p]='\0';//Last character='\0'
    s1--;
    s2--;
    p--;
    while(s1>=0&&s2>=0)//Addition by the characters
    {
        sum = (int)(c1.str[s1]-'0')+(int)(c2.str[s2]-'0');//adding the  characters from last
        sum+=carry;//adding carry
        carry=sum/10;//if carry is present
        sum=sum%10;
        ans.str[p]=(char)(sum+48);//storing by converting into char
        s1--;
        s2--;
        p--;
    }
    if(s1>-1)//Case where c1 is not completed
    {
        while(s1>-1)
        {
            sum=(int)(c1.str[s1]-'0')+carry;
            carry=sum/10;
            sum=sum%10;
            ans.str[p]=(char)(sum+48);
            p--;
            s1--;
        }
    }
    else if(s2>-1)//case where c2 is not completed
    {
        while(s2>-1)
        {
            sum=(int)(c2.str[s2]-'0')+carry;
            carry=sum/10;
            sum=sum%10;
            ans.str[p]=(char)(sum+48);
            p--;
            s2--;
        }
    }
    char max[310]="179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215";
    int flag=0;
    if(ans.length==309)//checking the over flow i.e. greater than 2^1024-1 or not
    {
        int i=0;
        while(i<309&&flag==0)
        {
            if(ans.str[i]>max[i])
            {
                flag=1;
            }
            else if(ans.str[i]<max[i])
            {
                flag=-1;
            }
            i++;
        }
    }
    if(flag==1)//greater than 2^1024-1 over flow
    {
        printf("There is an over flow in the addition please check the values given\n");
    }
    else if(flag==0 && carry>0&&ans.length==309)//equals to 2^1024-1 but there is carry which makes greater than 2^1024-1 again owerflow
    {
        printf("There is an over flow in the addition please check the values given\n");
    }
    else if(flag<=0)//In range so printing it
    {
        printf("The sum of 2 numbers is ");
        if(carry!=0)
        {
            printf("%d",carry);
        }
        int i=0;
        while(ans.str[i]!=('\0'))
        {
            printf("%c",ans.str[i]);
            i++;
        }
        printf("\n");
    }
}
void bigintsubtraction(bigint c1,bigint c2)//Bigint subtraction here c1>c2 managed by precheck in the main
{
    bigint ans;
    int p=(c1.length>c2.length)? c1.length:c2.length;//storing max length as max length of c1.len,c2.len
    int ap=p;
    ans.length=p;
    int carry=0,sub;//Initially there is no value carried so 0
    int s1=c1.length,s2=c2.length;
    ans.str[p]='\0';//Last character='\0'
    s1--;
    s2--;
    p--;
    while(s1>=0&&s2>=0)
    {
        if(c1.str[s1]>c2.str[s2])//no carry taken from previous
        {
            sub = (int)(c1.str[s1]-'0')-(int)(c2.str[s2]-'0')-carry;
            carry=0;
        }
        else if(c1.str[s1]==c2.str[s2]&&carry==1)//carry taken from previous case
        {
            sub=9;
            carry=1;
        }
        else if(c1.str[s1]==c2.str[s2]&&carry==0)//no carry taken from previous
        {
            sub=0;
            carry=0;
        }
        else if(c1.str[s1]<c2.str[s2])//carry taken from previous cas
        {
            sub= (int)(c1.str[s1]-'0')-(int)(c2.str[s2]-'0')-carry;
            sub=sub+10;
            carry=1;
        }
        ans.str[p]=(char)(sub+48);
        p--;
        s1--;
        s2--;
    }
    if(s1>=0)//when c1 is not completed
    {
        while(s1>-1)
        {
            if(carry==1&&c1.str[s1]<'1')
            {
                sub=9;
                carry=1;
            }
            else if(carry==1)
            {
                sub= (int)(c1.str[s1]-'0')-carry;
                carry=0;
            }
            else
            {
                sub= (int)(c1.str[s1]-'0');
                carry=0;
            }
            ans.str[p]=(char)(sub+48);
            p--;
            s1--;
        }
    }
    int i=0;
    while(ans.str[i]=='0'&& ans.str[i]!='\0')//not printing if there are any zeros in the start
    {
        i++;
    }
    if(i==ap)// if both the numbers are equal
    {
        printf("0");
    }
    else//printing remaining char other than 0
    {
        while(ans.str[i]!='\0')
        {
            printf("%c",ans.str[i]);
            i++;
        }
    }
    printf("\n");
}
void bigintmultiplication(bigint c1,bigint c2)//Bigint multiplication
{
    bigint ans;
    bigintinitialize(&ans,c1.length,c2.length);//initializing the ans string array
    int p=ans.length,i,j;
    int carry=0;
    int prod;
    int flag=0;
    if(p>309)//check for over flow
    {
        flag=1;
    }
    for(i=c2.length-1;flag==0&&i>-1;i--)//doing multiplication in a manner how we used to do in our childhood
    {
        for(j=c1.length-1;flag==0&&j>-1;j--)
        {
            prod=(int)(c2.str[i]-'0')*(int)(c1.str[j]-'0') + carry+(int)(ans.str[i+j+1]-'0');
            carry=prod/10;
            prod=prod%10;
            ans.str[i+j+1]=(char)(48+prod);
        }
    }
    char max[310]="179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215";
    if(ans.length==309&&flag==0)//checking overflow when digits equal to 309
    {
        i=0;
        while(i<309&&flag==0)
        {
            if(ans.str[i]>max[i])
            {
                flag=1;
            }
            else if(ans.str[i]<max[i])
            {
                flag=-1;
            }
            i++;
        }
    }
    if(flag==1)//printing overflow since greater than 2^1024-1
    {
        printf("There is an over flow in the multiplication please check the values given\n");
    }
    else if(flag==0&&carry>0&&ans.length==309)///printing overflow equal to 2^1024-1 and having a carry left which increases the length
    {
        printf("There is an over flow in the multiplication please check the values given\n");
    }
    else if(flag<=0)//printing the answer if no error
    {
        i=0;
        while(i<p&&ans.str[i]=='0')
        {
            i++;
        }
        if(carry!=0)
        {
            printf("%d",carry);
        }
        while(i<p&&ans.str[i]!='\0')
        {
            printf("%c",ans.str[i]);
            i++;
        }
        printf("\n");
    }
}
int main()
{
    int i;
    char op,temp;//addressing the operation by used
    bigint c1,c2;
    char max[310]="179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215";
    int flag1=0,flag2=0;//for the check of overflow in c1,c2
    printf("Enter + for addition\nEnter - for subtraction\nEnter * for multiplication\nEnter the operation needed to perform : ");
    scanf("%c",&op);//scanning operator +/-/*
    scanf("%c",&temp);//In buffer whn you press enter there is \n charecter so we use dummy variable to not to cause error
    while(!(op=='*'||op=='+'||op=='-'))//scanning until we get +/-/*
    {
        printf("Please enter the valid operations only +/-/* : ");
        scanf("%c",&op);
        scanf("%c",&temp);
    }
    printf("Enter the first number:");
    i=0;
    c1=bigintscan(c1);
    printf("Enter the second number:");
    c2=bigintscan(c2);
    if(c1.length==309||c2.length==309)//Overflow check if any of the length is 309
    {
        if(c1.length==309)
        {
            i=0;
            while(i<309&&flag1==0)
            {
                if(c1.str[i]>max[i])
                {
                    flag1=1;
                }
                else if(c1.str[i]<max[i])
                {
                    flag1=-1;
                }
                i++;
            }
        }
        if(c2.length==309)
        {
            i=0;
            while(i<309&&flag2==0)
            {
                if(c2.str[i]>max[i])
                {
                    flag2=1;
                }
                else if(c2.str[i]<max[i])
                {
                    flag2=-1;
                }
                i++;
            }
        }
    }
    if(c1.length>309||c2.length>309)//any of the string has more digits than 309 is over flow
    {
        printf("There is over flow in the entered numbers please enter number that is less than 2^1024\n");
    }
    else if(flag1>0||flag2>0)//over flow with 309 digits
    {
        printf("There is over flow in the entered numbers please enter number that is less than 2^1024\n");
    }
    else if(c1.length==0 || c2.length==0)//if empty input is given
    {
        printf("Please check the number's one or more number is empty\n");
    }
    else if(op=='+' && flag1==0 && c2.length>1 && c1.length==309)//if one of the number is 2^1024-1 and there is addition of some number so overflow
    {
        printf("There is over flow in the addition please enter numbers again\n");
    }
    else if(op=='+' && flag1==0 && c2.length==1 && c2.str[0]!='0' && c1.length==309)//if one of the number is 2^1024-1 and there is addition of some single digit number so overflow
    {
        printf("There is over flow in the addition please enter numbers again\n");
    }
    else if(op=='+' && flag2==0 && c1.length>1 && c2.length==309)//if one of the number is 2^1024-1 and there is addition of some number so overflow
    {
        printf("There is over flow in the addition please enter numbers again\n");
    }
    else if(op=='+' && flag2==0 && c1.length==1 && c1.str[0]!='0' && c2.length==309)//if one of the number is 2^1024-1 and there is addition of some single digit number so overflow
    {
        printf("There is over flow in the addition please enter numbers again\n");
    }
    else if(op=='+' && flag1<=0 && flag2<=0)
    {
        if(c1.length==1&&c1.str[0]=='0'&&c2.length==1&&c2.str[0]=='0')//when both the strings are 0
        {
            printf("The addition of the 2 numbers is 0\n");
        }
        else if(c1.length==1&&c1.str[0]=='0')//when one of the string is 0
        {
            printf("The addition of the 2 numbers is %s\n",c2.str);
        }
        else if(c2.length==1&&c2.str[0]=='0')//when one of the string is 0
        {
            printf("The addition of the 2 numbers is %s\n",c1.str);
        }
        else
        {
            bigintaddition(c1,c2);
        }
    }
    else if(op=='-'&&flag1<=0&&flag2<=0)
    {
        if(c1.length==1&&c1.str[0]=='0'&&c2.length==1&&c2.str[0]=='0')//If both numbers are 0
        {
            printf("The subtraction of 2 numbers is 0\n");
        }
        else if(c1.length==1&&c1.str[0]=='0')//if first number is 0
        {
            printf("The subtraction of 2 numbers is -%s\n",c2.str);
        }
        else if(c2.length==1&&c2.str[0]=='0')//if second number is 0
        {
            printf("The subtraction of 2 numbers is %s\n",c1.str);
        }
        else if(c1.length>c2.length)//based on the length we check the result is positive or negative
        {
            printf("The subtraction of 2 numbers is ");//positive result
            bigintsubtraction(c1,c2);
        }
        else if(c1.length<c2.length)
        {
            printf("The subtraction of 2 numbers is -");//negative result so passing reversely with printing - sign
            bigintsubtraction(c2,c1);
        }
        else//if length is equal then we need to check up to differentiating character
        {
            i=0;
            int flag=0;
            while(flag==0 && i<c1.length)
            {
                if(c1.str[i]>c2.str[i])
                {
                    flag=1;
                }
                else if(c1.str[i]<c2.str[i])
                {
                    flag=2;
                }
                i++;
            }
            if(flag==0&&i==c1.length)//both equal with same digits
            {
                printf("The subtraction of 2 numbers is 0\n");
            }
            else if(flag==1)//c1>c2 so positive
            {
                printf("The subtraction of 2 numbers is ");
                bigintsubtraction(c1,c2);
            }
            else if(flag==2)//c2>c1 so negative and passing reverse order
            {
                printf("The subtraction of 2 numbers is -");
                bigintsubtraction(c2,c1);
            }
        }
    }
    else if(op=='*'&&flag1<=0&&flag2<=0)//bigint multiplication
    {
        if((c1.length==1&&c1.str[0]=='0')||(c2.length==1&&c2.str[0]=='0'))//any one of the number is 0
        {
            printf("The multiplication of 2 given numbers is 0");
        }
        else if(c1.length==1&&c1.str[0]=='1')//any number is 1
        {
            printf("The multiplication of 2 given numbers is %s\n",c2.str);
        }
        else if(c2.length==1&&c2.str[0]=='1')//any number is 1
        {
            printf("The multiplication of 2 given numbers is %s\n",c1.str);
        }
        else//general case
        {
            printf("The multiplication of 2 given numbers is ");
            bigintmultiplication(c1,c2);
        }
    }
}
