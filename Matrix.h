class Matrix
{
  public:
  Matrix(int rows,int cols):rows(rows),cols(cols)
  {
    M = new float[rows][col];
  };
  float operator[](int row, int col)
  {
    return M[row][col];
  };
  float operator[](int i)
  {
    int r = floor(i/rows);
    int c = i%rows;
    return M[r][c];
  }
  Matrix& operator*(Matrix b)
  {
    int m = rows;
    int p = cols;
    int n = b.getCols();
    Matrix C(m,n);
    int i, j, k;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			C[n*i+j]=0;
			for (k=0;k<p;k++)
				C[n*i+j]= C[n*i+j]+M[p*i+k]*B[n*k+j];
		}
    return C;
  };
  int getRows()
  {
    return rows;
  };
  int getCols()
  {
    return cols;
  };
  void setVal(int row, int cols, float number)
  {
    M[row][col] = number;
  };
  private:
  float M;
  int rows,cols;
  
};
