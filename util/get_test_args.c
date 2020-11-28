/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: functions for test arguments and test iteration specification
*/

#include <libgen.h>
#include "GraphBLAS.h"
#include "test_utils.h"

// limits for built-in object arrays
int spec_limits(spec inspec)
{
  switch (inspec) {
  case TYPE: return num_Types();
  case SEMI: return num_Semirings();
  case MON: return num_Monoids();
  case BINOP: return num_BinaryOps();
  case UNOP: return num_UnaryOps();
  case SELOP: return num_SelectOps();
  case DESC: return num_Descriptors();
  case ACCUM: return num_BinaryOps();
  default: return 0;
  }
}

// string for spec, used for spec file output
void spec_string(spec inspec, char *instr)
{
  switch (inspec) {
  case TYPE: strcpy(instr, "TYPE"); break;
  case SEMI: strcpy(instr, "SEMI"); break;
  case MON: strcpy(instr, "MON"); break;
  case BINOP: strcpy(instr, "BINOP"); break;
  case UNOP: strcpy(instr, "UNOP"); break;
  case SELOP: strcpy(instr, "SELOP"); break;
  case DESC: strcpy(instr, "DESC"); break;
  case ACCUM: strcpy(instr, "ACCUM"); break;
  default: break;
  }
}

// apply a spec function and write to spec file
void print_spec(testargs *myargs, int **myspec)
{
  sprintf(myargs->spectest, "data/specfiles/%s%s.spec", myargs->testbase,
	  myargs->output); // spec output file
  FILE *specfp = fopen(myargs->spectest, "w"); // open spec file for writing
  if (!specfp) return; // do nothing if can't open file
  for (int i = 0; i < TOTAL; i++) {
    if (myspec[i]) {
      char ss[64];
      spec_string(i, ss);
      fprintf(specfp, "%s %d", ss, myspec[i][0]);
      if (myspec[i][0] < spec_limits(i)) {
	for (int j = 1; j <= myspec[i][0]; j++)
	  fprintf(specfp, " %d", myspec[i][j]);
      }
      fprintf(specfp, "\n");
    }
  }
  if (strlen(myargs->input0) > 0)
    fprintf(specfp, "INPUT0 %s\n", myargs->input0);
  if (strlen(myargs->input1) > 0)
    fprintf(specfp, "INPUT1 %s\n", myargs->input1);
  if (strlen(myargs->input2) > 0)
    fprintf(specfp, "INPUT2 %s\n", myargs->input2);
  if (strlen(myargs->mask) > 0)
    fprintf(specfp, "MASK %s\n", myargs->mask);
  if (strlen(myargs->initvals) > 0)
    fprintf(specfp, "INIT %s\n", myargs->initvals);
  if (strlen(myargs->output) > 0)
    fprintf(specfp, "OUTPUT %s\n", myargs->output);
  fclose(specfp);
}

// print input arguments
void print_args(testargs *myargs, GrB_Descriptor desc, GrB_BinaryOp accum)
{
  if (strlen(myargs->input0) > 0) printf("%s: %s\n", "input0", myargs->input0);
  if (strlen(myargs->input1) > 0) printf("%s: %s\n", "input1", myargs->input1);
  if (strlen(myargs->input2) > 0) printf("%s: %s\n", "input2", myargs->input2);
  if (strlen(myargs->mask) > 0) printf("%s: %s\n", "mask", myargs->mask);
  if (strlen(myargs->initvals) > 0)
    printf("%s: %s\n", "initvals", myargs->initvals);
  if (strlen(myargs->output) > 0) printf("%s: %s\n", "output", myargs->output);

  if (desc) GxB_print(desc, GxB_SUMMARY);
  if (accum) GxB_print(accum, GxB_SUMMARY);
}

// read parameters from file into spec array
void read_params(FILE *infp, spec inspec, int **myspec)
{
  int lim, rval;
  assert (fscanf(infp, "%d", &lim) == 1); // get number of values

  if (lim >= spec_limits(inspec)) { // one value for whole range
    if (!myspec[inspec]) {
      myspec[inspec] = malloc(sizeof(int));
      myspec[inspec][0] = spec_limits(inspec);
    }
  } else if (lim > 0) {
    int *read_vals;
    if (!myspec[inspec]) {
      read_vals = malloc((lim + 1) * sizeof(int)); read_vals[0] = lim;
      for (int i = 0; i < lim; i++) // read values and set
	assert (fscanf(infp, "%d", &read_vals[i + 1]) == 1);
      myspec[inspec] = read_vals;
    } else {
      for (int i = 0; i < lim; i++) // read values but don't set
	assert (fscanf(infp, "%d", &rval) == 1);
    }
  }
}

// read filenames into myarg structure
void read_filename(FILE *infp, char *carray)
{
  char str[128];
  assert (fscanf(infp, "%s", str) == 1); // scan the filename base
  strcpy(carray, str); // if not already given
}

// allocate and return clear spec
int **new_spec()
{
  int **myspec = malloc(TOTAL * sizeof(int *)); // fill test spec from args
  for (int j = 0; j < TOTAL; j++) myspec[j] = NULL;
  return myspec;
}

// get spec from input options
int **spec_from_args(testargs *myargs)
{
  int **myspec = new_spec();
  for (int j = 0; j < TOTAL; j++) { // initialize test spec
    if (myargs->specobj[j] >= spec_limits(j)) { // one value for whole range
      myspec[j] = malloc(sizeof(int));
      myspec[j][0] = spec_limits(j);
    } else if (myargs->specobj[j] >= 0) { // one value in array from args
      myspec[j] = malloc(2 * sizeof(int));
      myspec[j][0] = 1; myspec[j][1] = myargs->specobj[j];
    }
  }
  return myspec;
}

// read test spec from file
int **read_test_spec(testargs *myargs)
{
  int **myspec = spec_from_args(myargs);
  if (strlen(myargs->spectest) > 0) { // if spec file supplied
    FILE *infp; // if no file, run the default function and return spec
    if ((infp = fopen(myargs->spectest, "r")))  { // if spec file opened
      char str[64];
      while (fscanf(infp, "%s", str) == 1) { // loop over spec lines
	if (!strcmp(str, "TYPE")) read_params(infp, TYPE, myspec);
	else if (!strcmp(str, "SEMI")) read_params(infp, SEMI, myspec);
	else if (!strcmp(str, "MON")) read_params(infp, MON, myspec);
	else if (!strcmp(str, "BINOP")) read_params(infp, BINOP, myspec);
	else if (!strcmp(str, "UNOP")) read_params(infp, UNOP, myspec);
	else if (!strcmp(str, "SELOP")) read_params(infp, SELOP, myspec);
	else if (!strcmp(str, "DESC")) read_params(infp, DESC, myspec);
	else if (!strcmp(str, "ACCUM")) read_params(infp, ACCUM, myspec);
	else if (!strcmp(str, "MASK")) read_filename(infp, myargs->mask);
	else if (!strcmp(str, "INPUT0")) read_filename(infp, myargs->input0);
	else if (!strcmp(str, "INPUT1")) read_filename(infp, myargs->input1);
	else if (!strcmp(str, "INPUT2")) read_filename(infp, myargs->input2);
	else if (!strcmp(str, "OUTPUT")) read_filename(infp, myargs->output);
	else if (!strcmp(str, "INIT")) read_filename(infp, myargs->initvals);
	else  fgets(str, 256, infp); // comment
      }
      fclose(infp);
    }
  }
  return myspec;
}

static char fname_chars[TOTAL] = { 'T', 'S', 'M', 'B', 'U', 'L', 'D', 'A' };

// descriptor loop: innermost
bool test_D_loop(testargs *myargs, int **specptr, bool (*f)(testargs *))
{
  bool testerror = false;
  if (specptr[DESC]) {
    char bname[64]; strcpy(bname, myargs->output); // base from args
    int lim = specptr[DESC][0];
    for (int i = 0; i < lim; i++) { // descriptor loop
      if (lim >= spec_limits(DESC)) myargs->specobj[DESC] = i; // whole range
      else myargs->specobj[DESC] = specptr[DESC][i + 1]; // from spec
      sprintf(myargs->output, "%s_D%d", bname, myargs->specobj[DESC]);
      testerror |= f(myargs); // run the test
    }
    strcpy(myargs->output, bname); // restore output name
  } else { myargs->specobj[DESC] = -1; testerror |= f(myargs); } // run the test
  return testerror;
}

// loop over object then descriptor and accumulator
bool test_L_DA_loop(testargs *myargs, int **specptr, bool (*f)(testargs *))
{
  spec inspec = TOTAL;
  for (int i = 0; i < TOTAL; i++) if (specptr[i]) { inspec = i; break; }
  if (inspec == TOTAL) return true; // error: must have outer loop
  bool testerror = false;
  char bname[64]; strcpy(bname, myargs->output); // base from args
  int lim = specptr[inspec][0];
  for (int i = 0; i < lim; i++) { // outer loop
    if (lim >= spec_limits(inspec)) myargs->specobj[inspec] = i; // whole range
    else myargs->specobj[inspec] = specptr[inspec][i + 1]; // from spec
    if (inspec != TYPE) // type will be added to filename by test routines
      sprintf(myargs->output, "%s_%c%d", bname, fname_chars[inspec],
	      myargs->specobj[inspec]);

    if (specptr[ACCUM] && (i < specptr[ACCUM][0])) { // if there is accumulator
      myargs->specobj[ACCUM] = specptr[ACCUM][i + 1]; // add it to args
      char aname[64]; strcpy(aname, myargs->output); // add to filename
      sprintf(myargs->output, "%s_A%d", aname, myargs->specobj[ACCUM]);
    } else myargs->specobj[ACCUM] = -1; // otherwise, none

    testerror |= test_D_loop(myargs, specptr, f); // descriptor loop
  }
  strcpy(myargs->output, bname); // restore output name
  return testerror;
}

// loop over object: type, descriptor and accumulator
bool test_L_TDA_loop(testargs *myargs, int **specptr, bool (*f)(testargs *))
{
  assert (specptr[SELOP]); // must have outer loop
  bool testerror = false;
  char bname[64]; strcpy(bname, myargs->output); // base from args
  int lim = specptr[SELOP][0];
  for (int i = 0; i < lim; i++) { // outer loop
    if (lim >= spec_limits(SELOP)) myargs->specobj[SELOP] = i; // whole range
    else myargs->specobj[SELOP] = specptr[SELOP][i + 1]; // from spec
    sprintf(myargs->output, "%s_%c%d", bname, fname_chars[SELOP], // filename
	    myargs->specobj[SELOP]);
    testerror |= test_L_DA_loop(myargs, specptr, f);
  }
  strcpy(myargs->output, bname);
  return testerror;
}

// free test spec
void free_test_spec(int **myspec)
{
  for (int j = 0; j < TOTAL; j++) if (myspec[j]) free(myspec[j]);
  free(myspec);
}

// if select, loop over type for each select operator
bool test_loop(testargs *myargs, bool (*g)(testargs *))
{
  int **myspec = read_test_spec(myargs); // get the spec
  bool testerror;
  if (myspec[SELOP]) testerror = test_L_TDA_loop(myargs, myspec, g);
  else testerror = test_L_DA_loop(myargs, myspec, g); // run test
  free_test_spec(myspec);
  return testerror;
}

void gen_default(char *);

// read default file for list of spec files
bool test_spec_loop(testargs *myargs, bool (*g)(testargs *))
{
  if (myargs->generate) { // if spec file given, generate it
    gen_default(myargs->testbase); // defaults
    int **myspec = spec_from_args(myargs);
    if (strlen(myargs->spectest) > 0) print_spec(myargs, myspec);
    free_test_spec(myspec);
  }

  char lfname[256];
  sprintf(lfname, "data/specfiles/%s.list", myargs->testbase);
  FILE *infp; // file with list of spec files

  if ((strlen(myargs->spectest) == 0) && (infp = fopen(lfname, "r"))) {
    bool testerror = false;
    while (fscanf(infp, "%s", myargs->spectest) == 1) { // loop over lines
      testargs *myargsC = malloc(sizeof(testargs));
      memcpy(myargsC, myargs, sizeof(testargs));
      testerror |= test_loop(myargsC, g);
      free(myargsC);
    }
    fclose(infp); return testerror;
  } else return test_loop(myargs, g); // run test loop
}

// allocate and return clear args structure
testargs *new_args(char *testbasestr)
{
  testargs *myargs = malloc(sizeof(testargs));
  myargs->generate = false;
  for (int i = 0; i < TOTAL; i++) myargs->specobj[i] = -1;
  myargs->mask[0] = '\0'; // empty strings for filenames
  myargs->input0[0] = '\0';
  myargs->input1[0] = '\0';
  myargs->input2[0] = '\0';
  myargs->initvals[0] = '\0';
  myargs->output[0] = '\0';
  myargs->spectest[0] = '\0';
  strcpy(myargs->inbase, "testread"); // default input directory
  strcpy(myargs->testbase, testbasestr);
  return myargs;
}

// get test options and args: no testing of values
testargs *get_test_args(int argc, char **argv)
{
  testargs *myargs = new_args(basename(argv[0]));
  for (int i = strlen(myargs->testbase) - 1; i >= 0; i--)
    if (myargs->testbase[i] == '.') myargs->testbase[i] = '\0';

  if (argc == 1) return myargs; // no arguments or options

  int c, ui, ni, li, ti, bi, si, di, ai; // default no spec
  while ((c = getopt(argc, argv, "hgt:u:b:s:n:l:d:a:m:0:1:2:o:i:p:")) != -1) {
    switch (c) { // test parameters are options
    case 'h': printf("hgt:u:b:s:n:l:d:a:m:0:1:2:o:i:p:\n");
      printf("help, generate, type, unaryop, binaryop, semiring, monoid, selectop, descriptor, accum, mask, i0, i1, i2, out, init, spec\n");
      exit(0);
    case 'g': myargs->generate = true; break;
    case 't': ti = atol(optarg); myargs->specobj[TYPE] = ti; break;
    case 'u': ui = atol(optarg); myargs->specobj[UNOP] = ui; break;
    case 'b': bi = atol(optarg); myargs->specobj[BINOP] = bi; break;
    case 's': si = atol(optarg); myargs->specobj[SEMI] = si; break;
    case 'n': ni = atol(optarg); myargs->specobj[MON] = ni; break;
    case 'l': li = atol(optarg); myargs->specobj[SELOP] = li; break;
    case 'd': di = atol(optarg); myargs->specobj[DESC] = di; break;
    case 'a': ai = atol(optarg); myargs->specobj[ACCUM] = ai; break;
    case 'm': strcpy(myargs->mask, optarg); break;
    case '0': strcpy(myargs->input0, optarg); break; // left to right
    case '1': strcpy(myargs->input1, optarg); break;
    case '2': strcpy(myargs->input2, optarg); break;
    case 'o': strcpy(myargs->output, optarg); break;
    case 'i': strcpy(myargs->initvals, optarg); break; // needed if accum
    case 'p': strcpy(myargs->spectest, optarg); break; // needed if accum
    }
  }
  // get file directory from argument
  if (optind < argc) {
    strcpy(myargs->inbase, argv[optind]);
    strcpy(myargs->testbase, argv[optind++]);
  }
  return myargs;
}

// read default file for list of spec files
bool run_test(int argc, char **argv, bool (*g)(testargs *))
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

  bool testerror = test_spec_loop(myargs, g);

  OK(GrB_finalize());
  return testerror;
}
