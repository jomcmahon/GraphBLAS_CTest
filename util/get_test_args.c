/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

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

// print input arguments
void print_args(testargs *myargs, GrB_Descriptor desc, GrB_BinaryOp accum)
{
  GrB_Info info;
  if (strlen(myargs->input0) > 0) printf("%s: %s\n", "input0", myargs->input0);
  if (strlen(myargs->input1) > 0) printf("%s: %s\n", "input1", myargs->input1);
  if (strlen(myargs->input2) > 0) printf("%s: %s\n", "input2", myargs->input2);
  if (strlen(myargs->mask) > 0) printf("%s: %s\n", "mask", myargs->mask);
  if (strlen(myargs->initvals) > 0)
    printf("%s: %s\n", "initvals", myargs->initvals);
  if (strlen(myargs->output) > 0) printf("%s: %s\n", "output", myargs->output);

  if (desc) OK (GxB_print(desc, GxB_SUMMARY));
  if (accum) OK (GxB_print(accum, GxB_SUMMARY));
}

// read parameters from file into spec array
void read_params(FILE *infp, spec inspec, int **myspec)
{
  int lim, rval;
  assert (fscanf(infp, "%d", &lim) == 1); // get number of values

  if ((inspec != ACCUM) && (lim >= spec_limits(inspec))) { // whole range
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
      char str[8192];
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

// free test spec
void free_test_spec(int **myspec) {
    for (int j = 0; j < TOTAL; j++)
        if (myspec[j])
            free(myspec[j]);
    free(myspec);
}

// set the argument in the test args structure based on spec
void set_spec_arg(spec inspec, int **specptr, int lim, testargs *myargs, int i)
{
  if (inspec != TOTAL) { // valid spec
    int val = -1; // default no argument
    if ((inspec != ACCUM) && (lim >= spec_limits(inspec))) val = i; // range
    else if (specptr[inspec] && (i < specptr[inspec][0]))
      val = specptr[inspec][i + 1]; // from spec

    if (val >= 0) { // if there is arg, add to file name
      char sname[64];
      sprintf(sname, "_%c%d", fname_chars[inspec], val);
      strcat(myargs->output, sname);
    }
    myargs->specobj[inspec] = val;
  }
}

// get loop limit for current iteration
int get_loop_limit(spec inspec, int **specptr)
{
  if ((inspec != TOTAL) && specptr[inspec]) return specptr[inspec][0];
  else return 1;
}

// loop over selectors, primary object, then descriptors
bool test_loop(testargs *myargs, bool (*f)(testargs *))
{
  int **specptr = read_test_spec(myargs); // get the spec
  bool testerror = false;

  char name1[64];
  strcpy(name1, myargs->output); // save the file name for next iteration
  int lim1 = get_loop_limit(SELOP, specptr); // get select op limit
  for (int i = 0; i < lim1; i++) { // loop over selector if there are any
    set_spec_arg(SELOP, specptr, lim1, myargs, i);

    spec inspec = TOTAL; // get first available spec from enumerator
    for (int i = 0; i < TOTAL; i++) // order determines precedence
      if (specptr[i]) { inspec = i; break; }

    char name2[64];
    strcpy(name2, myargs->output); // save the file name for next iteration
    int lim2 = get_loop_limit(inspec, specptr); // get spec limit
    for (int j = 0; j < lim2; j++) { // loop over spec if there are any
      set_spec_arg(inspec, specptr, lim2, myargs, j);
      set_spec_arg(ACCUM, specptr, 0, myargs, j); // no full range for accum

      char name3[64];
      strcpy(name3, myargs->output); // base from args
      int lim3 = get_loop_limit(DESC, specptr); // get descriptor limit
      for (int k = 0; k < lim3; k++) { // descriptor loop
	set_spec_arg(DESC, specptr, lim3, myargs, k);
	testerror |= f(myargs); // run the test
	strcpy(myargs->output, name3); // restore output name
      }
      strcpy(myargs->output, name2); // restore output name
    }
    strcpy(myargs->output, name1); // restore output name
  }
  free_test_spec(specptr);
  return testerror;
}

// read default file for list of spec files
bool test_spec_loop(testargs *myargs, bool (*g)(testargs *))
{
  // if no spec file and output not specified, use list file
  if ((strlen(myargs->spectest) == 0) && (strlen(myargs->output) == 0)) {
    char lfname[256];
    sprintf(lfname, "data/specfiles/%s.list", myargs->testbase);
    FILE *infp = fopen(lfname, "r"); // file with list of spec files
    if (infp) {
      bool testerror = false;
      while (fscanf(infp, "%s", myargs->spectest) == 1) { // loop over lines
	testargs *myargsC = malloc(sizeof(testargs));
	memcpy(myargsC, myargs, sizeof(testargs));
	testerror |= test_loop(myargsC, g);
	free(myargsC);
      }
      fclose(infp); return testerror;
    } return true; // must have output file or spec or list file
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
  OK (GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

  bool testerror = test_spec_loop(myargs, g);

  OK (GrB_finalize());
  return testerror;
}
