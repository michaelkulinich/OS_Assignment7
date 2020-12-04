#define PAGEREF_MAX 40

// runs Fist-In-First-Out Algorithm on array of integers
// returns number of page faults
int FIFO(int *str)
{
  // total number of page faults in reference string
  int count_faults = 0;

  // flag used to determin if page was found in page-frames. 1 = page fault.
  int fault = 1;
  int frame[4];
  for(int i=0; i < PAGEREF_MAX ; ++i) {
    if (str[i] == -1)
      break;
    for(int j = 0; j < 4; ++j) {
      if (frame[j] == str[i]) {
        fault = 0;
        break;
      }
    }
    // if the page is not in the page-frames, we have a fault
    // then replace the oldest page in the page-frames
    if (fault) {
      frame[i % 4] = str[i];  // circular array
      count_faults++;  
    }
    else {
      fault = 1;
    }
  }

  return count_faults;
}



// runs Last-Recently-Used Algorithm on array of integers
// returns number of page faults
int LRU(int *str)
{
  // number of page faults in reference string
  int count_faults = 0;

  int fault = 1;
  int frame[4];
  for (int i=0 ; i < PAGEREF_MAX ; ++i){ // for each number in ref string
    if (str[i] == -1)
      break;
    // fill in first 4 frames
    if (i < 4){
      frame[i] = str[i];
      count_faults++;
      continue;
    }

    // check if page ref is in main memory
    for(int j = 0; j < 4; ++j) {
      if (frame[j] == str[i]) {
        // if so, move page to front and move the rest down
        int temp = frame[j];
        for (int k=j ; k > 0 ; --k){
          frame[k] = frame[k-1];
        }
        frame[0] = temp;
        fault = 0;
      }
    }
    
    // if the page is not in the page-frames, we have a fault
    // then replace the first page and move the rest down
    if (fault) {
        for (int k=3 ; k > 0 ; --k){
          frame[k] = frame[k-1];
        }
        frame[0] = str[i];
      count_faults++;
    }
    else {
      fault = 1;
    }
  }

  return count_faults;
}



// runs Optimal Algorithm on array of integers
// returns number of page faults
int Optimal(int *str)
{
// total number of page faults in reference string
  int count_faults = 0;

  // flag used to determin if page was found in page-frames. 1 = page fault.
  int fault = 1;

  // number of frames
  int frameSize = 4;

  // arrays to store frames and frame indexes
  int frame[frameSize];
  int temp[frameSize];
  int boolArrayFrame[frameSize]; // each index corresponds to frame[] index

  // initialize each array
  for (int i = 0; i < frameSize; ++i) {
    frame[i] = -1;
    temp[i] = -1;
    boolArrayFrame[i] = 0;
  }

  // Start iterating through the reference string
  for(int i = 0; i < PAGEREF_MAX; ++i) {
    if (str[i] == -1) {
      break;
    }
    for(int j = 0; j < frameSize; ++j) {
      if (frame[j] == str[i]) {
        fault = 0;
        break;
      }
    }

    // if the page is not in the page-frames, we have a fault
    // then replace the page that will not be used for the longest time
    if (fault) {

      int indexTemp = 0;
      int stop = 1;
      int filledEmptyFrame = 0;

      // iterate through the rest of the reference string, flag stop is included so that
      // we can break out of nested loop
      for (int k = i + 1; k < PAGEREF_MAX && stop; ++k) {

        // iterate through all the frames and see if the frame is used in the remaining reference string
        for (int m = 0; m < frameSize && stop; ++m) {
          // Filling up the frames if they are empty
          if (frame[m] == -1) {
            temp[indexTemp] = m;
            indexTemp++;
            stop = 0;
            filledEmptyFrame = 1;
          }

          // if the frame page is used later in the reference string
          else if (frame[m] == str[k]) { 
            int dontFillTemp = 0;
            for (int j = 0; j < frameSize; ++j) {

              // if the frame is already in the temp array, 
              if (temp[j] == m) { 
                dontFillTemp = 1;
              }
            }
            if (!dontFillTemp){ 
              temp[indexTemp] = m;
              indexTemp++;
            }
          }
        }
      }
      // if we are at the last page in string, and the frames are full of pages
      // then replace any page
      if (i == PAGEREF_MAX - 1 && frame[frameSize -1] != -1) {
        frame[0] = str[i];
      }

      // if we are at the last page in string, and the frames are NOT all filled
      // then add the page into the frame that is empty
      // (this will only happen if the number of pages in reference string is less than frame size)
      else if (i == PAGEREF_MAX -1) {
        for(int j = 0; j < PAGEREF_MAX; j++) {
          if (frame[j] == -1) {
            frame[j] = str[i];
          }
        }
      }

      // some frames are still empty so we need to fill them
      else if (filledEmptyFrame) {
        frame[temp[indexTemp-1]] = str[i];
      }

      else {

        // if none of the pages in the frames will be used again
        if (indexTemp == 0) {
          frame[0] = str[i];
        }
        else {
          for (int j = 0; j < frameSize; ++j) {
            if(temp[j] != -1) {
              boolArrayFrame[temp[j]] = 1;  // the frame at index (temp[j]) is used again later on in the reference string
            }
          }
          int allUsedAgainLater = 1;
          for (int j = 0; j < frameSize; ++j) {

            // the frame at index j is NOT used agian later on in the reference string
            // so we fill that spot up with the new page
            if(!boolArrayFrame[j]) {  
              frame[j] = str[i];
              allUsedAgainLater = 0;
              break;
            }
          }

          // original case, replace the page that will not be used for the longest time
          if (allUsedAgainLater) {
            frame[temp[indexTemp-1]] = str[i];
          }
        }
      }
      count_faults++;  
    }
    else {
      fault = 1;
    }
  }

  return count_faults;
}