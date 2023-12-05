#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>

typedef struct review {
 int review_id;
 int movie_id;
 int user_id;
 char review[100];
 int rating;
 time_t timestamp;
}review;

typedef struct user
{
 int user_id;
 char f_name[20];
 char l_name[20];
 char mob_no[12];
 char email[20];
 char pass[20];
 struct dob
 {
 int day;
 int month;
 int year;
 }dob;
}user;

typedef struct movies {
 int id;
 char title[50];
 char releasedate[50];
}movies;

void sign_in(user *u);
void sign_up(user *u);
void logged_in(user *user, int id);
int edit_profile(user *u,int id);
void update(user *u);
int change_password(user *u,int id);
void password(user *u);
void displayallmovies();
void displayreview(review *r);
review * write_review(review *r,int id);
void displayAllReviews(review *reviews, int numReviews);
void displayMyReview(review *reviews, int numReviews, int MyId);
void edit_review(review *reviews,int id);
void delete_review(review *reviews,int id);

int u_id = 0;
struct review re;
review reviewsArray[100]; 
int numReviews = 0;
int r_id= 0;

int main()
{
 int choice;
 user u[20];
 
 do
 {
 printf("0.Exit\n1.Sign In\n2.Sign Up\n");
 printf("Enter choice: ");
 scanf("%d", &choice);

 switch(choice)
 {
 case 1:
 sign_in(u);
 break;

 case 2:
 sign_up(u);
 break;

 default:
 printf("Invalid choice....(:\n");
 break;
 }

 }while(choice != 0);

 return 0;
}

void sign_in(user *u)
{
 char email[20];
 char pass[20];
 printf("Enter Email: ");
 scanf("%*c%[^\n]s",email);
 printf("Enter Password: ");
 scanf("%*c%[^\n]s",pass);
 
 user temp;
 int temp_id;
 
 FILE *fptr = fopen("user_data.txt", "a+");
 if(fptr == NULL)
 {
 perror("failed to open user data file\n");
 exit(1);
 }

 while(fread(&temp, sizeof(user), 1, fptr) != 0)
 {
 // printf("email:%s\npasas:%s\n",temp.email, temp.pass);
 if((strcmp(temp.email, email) ==0 && strcmp(temp.pass, pass)==0))
 {
 temp_id = temp.user_id ; //get id of match user
 printf("matched id = %d\n", temp_id);
 logged_in(u, temp_id); //user id passing
 return;
 }
 }
 printf("user not found....:(");
}

void sign_up(user *u)
{
 printf("Enter First name: ");
 scanf("%*c%[^\n]s",u[u_id].f_name);
 printf("Enter Last name: ");
 scanf("%*c%[^\n]s",u[u_id].l_name);
 printf("Enter Mobile: ");
 scanf("%*c%[^\n]s",u[u_id].mob_no);
 printf("Enter Email: ");
 scanf("%*c%[^\n]s",u[u_id].email);
 printf("Enter Password: ");
 scanf("%*c%[^\n]s",u[u_id].pass);
 printf("Enter Date Of Birth\n");
 printf("Enter Day:");
 scanf("%d",&u[u_id].dob.day);
 printf("Enter Month:");
 scanf("%d",&u[u_id].dob.month);
 printf("Enter Year:");
 scanf("%d",&u[u_id].dob.year);
 u[u_id].user_id = u_id; //id assign

 user temp = u[u_id]; //temp variable to write into file
 FILE *fptr = fopen("user_data.txt", "a+");
 if(fptr == NULL){
 perror("failed to open user data file\n");
 exit(1);
 }

 fwrite(&temp, sizeof(user), 1, fptr);
 
 fread(&temp, sizeof(user), 1, fptr);
/*
 printf("Enter First name: %s\n",temp.f_name);
 printf("Enter Last name: %s\n",temp.l_name);
 printf("Enter Mobile: %s\n",temp.mob_no);
 printf("Enter Email: %s\n",temp.email);
 printf("Enter Password: %s\n",temp.pass);
*/
 fclose(fptr);
 u_id++;

 printf("\nYour new account has been created! Use your info to login!\n");
}

void logged_in(user *u, int id)
{
 int choice;
 do
 {
 printf("\n0.Sign out\n1.Edit Profile\n2.Change Password\n3.Write Review\n4.Edit Review\n5.Display All Movies\n6.Display All Reviews\n7.My review\n10.Delete Review\n");
 printf("Enter choice: ");
 scanf("%d", &choice);
 
 switch(choice)
 {
 case 1:
 printf("Edit Profile!!!!\n");
 edit_profile(u,id);
 break;
 case 2:
 printf("Change Password!!!!\n");
 change_password(u,id);
 break;
 case 3:
 review *re = write_review(&reviewsArray[numReviews],id);
 numReviews++;
 displayreview(re);
 break;
 case 4:
 edit_review(re,id);
 break;
 case 5:
 displayallmovies();
 break;
 case 6:
 displayAllReviews(reviewsArray, numReviews);
 break;
 case 7:
 displayMyReview(reviewsArray, numReviews, id);
 break;
 case 8:
 //change_pass(user, id);
 break;
 case 9:
 //edit_profile(id);
 case 10:
 delete_review(re,id);
 break;
 default:
 return;
 }

 }while(choice != 0);
}

int edit_profile(user *u,int id)
{


 FILE *file;
 int userIdToEdit = id;

 // Open the file in read-write mode
 file = fopen("user_data.txt", "r+");
 
 if (file == NULL) {
 printf("Error opening file!\n");
 return 1;
 }

 

 struct user currentUser;

 while (fread(&currentUser, sizeof(struct user), 1, file)) {
 if (currentUser.user_id == userIdToEdit) {
 
 update(&currentUser);
 
 
 fseek(file, -sizeof(struct user), SEEK_CUR);
 
 
 fwrite(&currentUser, sizeof(struct user), 1, file);
 
 printf("\nProfile updated successfully!!!\n");
 
 
 fclose(file);
 
 return 0;
 }
 }

 fclose(file);
 
}

void update(struct user *u)
{
 
 printf("Do You Want To Change First Name ?\n");
 printf("y/n\n");
 char ch;
 scanf("%*c%[^\n]c",&ch);
 if(ch == 'y')
 {
 char str[20];
 printf("Enter New First Name : ");
 scanf("%*c%[^\n]s",str);
 strcpy(u->f_name,str);
 
 }

 printf("Do You Want To Change Last Name ?\n");
 printf("y/n\n");
 scanf("%*c%[^\n]c",&ch); 
 if(ch == 'y')
 {
 char str[20];
 printf("Enter New Last Name : ");
 scanf("%*c%[^\n]s",str);
 strcpy(u->l_name,str);
 }
 
 printf("Do You Want To Change Mobile Number ?\n");
 printf("y/n\n");
 scanf("%*c%[^\n]c",&ch);
 if(ch == 'y')
 {
 char str[20];
 printf("Enter New Mobile Number : ");
 scanf("%*c%[^\n]s",str);
 strcpy(u->mob_no,str);
 }
 
 printf("Do You Want To Change EmailID ?\n");
 printf("y/n\n");
 scanf("%*c%[^\n]c",&ch);
 if(ch == 'y')
 {
 char str[20];
 printf("Enter New EmailID : ");
 scanf("%*c%[^\n]s",str);
 strcpy(u->email,str);
 }
 
 printf("Do You Want To Change DOB ?\n");
 printf("y/n\n");
 scanf("%*c%[^\n]c",&ch);
 if(ch == 'y')
 {
 printf("Enter Date Of Birth\n");
 printf("Enter Day:");
 scanf("%d",&u->dob.day);
 printf("Enter Month:");
 scanf("%d",&u->dob.month);
 printf("Enter Year:");
 scanf("%d",&u->dob.year);
 }

}

int change_password(user *u,int id)
{
 FILE *file;
 int userIdToEdit = id;

 // Open the file in read-write mode
 file = fopen("user_data.txt", "r+");
 
 if (file == NULL) {
 printf("Error opening file!\n");
 return 1;
 }

 

 struct user currentUser;

 while (fread(&currentUser, sizeof(struct user), 1, file)) {
 if (currentUser.user_id == userIdToEdit) {
 
 password(&currentUser);
 
 
 fseek(file, -sizeof(struct user), SEEK_CUR);
 
 
 fwrite(&currentUser, sizeof(struct user), 1, file);
 
 printf("\nPassword updated successfully!!!\n");
 
 
 fclose(file);
 
 return 0;
 }
 }

 fclose(file);

}

void password(user *u)
{
 printf("Do You Want To Change Password ?\n");
 printf("y/n\n");
 char ch;
 scanf("%*c%[^\n]c",&ch);
 if(ch == 'y')
 {
 char str[20];
 printf("Enter New Password : ");
 scanf("%*c%[^\n]s",str);
 strcpy(u->pass,str);
 
 }
 
}

void displayallmovies()
{
 struct movies movieList[10];


 movieList[0].id = 1;
 strcpy(movieList[0].title, "Welcome");
 strcpy(movieList[0].releasedate, "2010-07-16");

 movieList[1].id = 2;
 strcpy(movieList[1].title, "Dhol");
 strcpy(movieList[1].releasedate, "2008-07-18");

 movieList[2].id = 3;
 strcpy(movieList[2].title, "De Dana Dan");
 strcpy(movieList[2].releasedate, "2008-07-21");

 movieList[3].id = 4;
 strcpy(movieList[3].title, "Dhamaal");
 strcpy(movieList[3].releasedate, "2008-07-19");

 movieList[4].id = 5;
 strcpy(movieList[4].title, "Phir Hera Pheri");
 strcpy(movieList[4].releasedate, "2008-07-20");

 movieList[5].id = 6;
 strcpy(movieList[5].title, "Hera Pheri");
 strcpy(movieList[5].releasedate, "2008-07-21");

 movieList[6].id = 7;
 strcpy(movieList[6].title, "Golmaal");
 strcpy(movieList[6].releasedate, "2008-07-22");

 movieList[7].id = 8;
 strcpy(movieList[7].title, "Nagin");
 strcpy(movieList[7].releasedate, "2008-07-23");

 movieList[8].id = 9;
 strcpy(movieList[8].title, "Suryavansham");
 strcpy(movieList[8].releasedate, "2008-07-24");

 movieList[9].id = 10;
 strcpy(movieList[9].title, "Ashi Hi Banva Banvi");
 strcpy(movieList[9].releasedate, "2008-02-25");

 
 printf("Movie List:\n");
 for (int i = 0; i < 10; i++) {
 printf("ID: %d\n", movieList[i].id);
 printf("Title: %s\n", movieList[i].title);
 printf("Release Date: %s\n", movieList[i].releasedate);
 printf("\n");
 }

}

review * write_review(review *r,int id)
{
 // printf("Enter Review ID: ");
 // scanf("%d", &r->review_id);
 r->review_id=r_id++;

 printf("Enter Movie ID: ");
 scanf("%d", &r->movie_id);

 r->user_id=id;

 // printf("Enter User ID: ");
 // scanf("%d", &r->user_id);

 printf("Enter Review (up to 99 characters): ");
 scanf(" %[^\n]", r->review); // %[^\n] to read a whole line

 printf("Enter Rating: ");
 scanf("%d", &r->rating);

 time(&r->timestamp);

 //r->timestamp = time(NULL);


 printf("\nReview successfully recorded!\n");
 return r;
}


void displayreview(review *r) 
{
 printf("\nReview ID: %d\n", r->review_id);
 printf("Movie ID: %d\n", r->movie_id);
 printf("User ID: %d\n", r->user_id);
 printf("Review: %s\n", r->review);
 printf("Rating: %d\n", r->rating);

 printf("Timestamp: %s", ctime(&r->timestamp));
 

 // Convert timestamp to a human-readable format
 // char buffer[26];
 // strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&r->timestamp));
 // printf("Timestamp: %s\n", buffer);
 printf("\n");
}

void displayAllReviews(review *reviews, int numReviews) {
 printf("All Reviews:\n");
 if(numReviews == 0)
 printf("List Is Empty!!!\n");
 else
 {
 for (int i = 0; i < numReviews; i++) 
 {
 printf("\n");
 printf("Review ID: %d\n", reviews[i].review_id);
 printf("Movie ID: %d\n", reviews[i].movie_id);
 printf("User ID: %d\n", reviews[i].user_id);
 printf("Review: %s\n", reviews[i].review);
 printf("Rating: %d\n", reviews[i].rating);
 printf("Timestamp: %s", ctime(&reviews[i].timestamp));
 //printf("Timestamp: %s\n", reviews[i].timestamp);
 printf("\n");
 }
 }
}


void displayMyReview(review *reviews, int numReviews, int MyId) 
{
 int flag=0;
 
 for (int i = 0; i < numReviews; i++) 
 {
 // printf("user id=%d\n",reviews[i].user_id);
 // printf("my id=%d\n",MyId);
 if (reviews[i].user_id == MyId) 
 {
 printf("\n");
 printf("Review ID: %d\n", reviews[i].review_id);
 printf("Movie ID: %d\n", reviews[i].movie_id);
 printf("User ID: %d\n", reviews[i].user_id);
 printf("Review: %s\n", reviews[i].review);
 printf("Rating: %d\n", reviews[i].rating);
 printf("Timestamp: %s", ctime(&reviews[i].timestamp));
 //printf("Timestamp: %s\n", reviews[i].timestamp);
 printf("\n");
 flag=1;
 //return; // Found the review, exit the function
 }
 }

 // If the reviewID is not found
 if(!flag)
 printf("Review with ID %d not found.\n", MyId);
}


void edit_review(review *reviews,int id)
{
 displayMyReview(reviewsArray, numReviews, id);
 int r_id;
 int flag=0;
 printf("Enter Review ID You Want To Edit : ");
 scanf("%d",&r_id);

 for (int i = 0; i < numReviews; i++) 
 {
 // printf("user id=%d\n",reviews[i].user_id);
 // printf("my id=%d\n",MyId);
 if (reviews[i].review_id == r_id) 
 {
 printf("\n");
 char new_review[100];
 printf("Write New Review : ");
 scanf(" %[^\n]", new_review); 
 strcpy(reviews->review,new_review);
 printf("New Review Added Successfully\n");
 flag=1;
 }
 }

 if(!flag)
 printf("Review with ID %d not found.\n", r_id);
}


void delete_review(review *reviews,int id)
{
 displayMyReview(reviewsArray, numReviews, id);
 int r_id;
 int flag=0;
 printf("Enter Review ID You Want To Delete : ");
 scanf("%d",&r_id);

 // for (int i = 0; i < numReviews; i++) 
 // {
 // if (reviews[i].review_id == r_id) 
 // {
 // printf("\n");
 // reviews[i].review_id = -1;
 // printf("Review Deleted Successfully\n");
 // flag=1;
 // }
 // }

 int i, j;
 for (i = 0; i <= numReviews; i++) {
 if (reviews[i].review_id == r_id) {
 // Found the review to delete, shifting the remaining elements
 for (j = i; j <= numReviews - 1; j++) {
 reviews[j] = reviews[j + 1];
 }
 // Decrease the number of reviews
 (numReviews)--;
 printf("Review Deleted Successfully\n");
 flag=1;
 break;
 }
 }

 if(!flag)
 printf("Review with ID %d not found.\n", r_id); 
}