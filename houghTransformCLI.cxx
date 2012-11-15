/**
 * Find the circles, dark tubes in the MR images
 */

// std
#include <string>
#include <iostream>
#include <fstream>

// vtk
#include "vtkSmartPointer.h"
#include "vtkPolyData.h"
#include "vtkPolyDataWriter.h"

// local
#include "utilitiesIO.h"
#include "utilitiesImage.h"

//itk
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImageRegionIterator.h"
#include "itkThresholdImageFilter.h"
#include "itkPluginUtilities.h"
#include "itkMinimumMaximumImageCalculator.h"
#include <itkGradientMagnitudeImageFilter.h>
#include <itkDiscreteGaussianImageFilter.h>
#include <list>
#include "itkCastImageFilter.h"
#include "vnl/vnl_math.h"

#include "itkHoughTransformRadialVotingImageFilter.h"

#include "houghTransformCLICLP.h"

#include <sstream>

// Use an anonymous namespace to keep class types and function names
// from colliding when module is used as shared object module.  Every
// thing should be in an anonymous namespace except for the module
// entry point, e.g. main()
//
namespace
{

} // end of anonymous namespace

int main( int argc, char * argv[] )
{
  PARSE_ARGS;  
  
  typedef    short InputPixelType;
  typedef    short OutputPixelType;
  
  const    unsigned int    Dimension = 3;
  typedef  float           InternalPixelType;
  
  typedef itk::Image< InputPixelType, Dimension >  InputImageType;
  typedef itk::Image< InternalPixelType, Dimension >    InternalImageType;
  typedef  itk::Image< OutputPixelType, Dimension >  OutputImageType;

  InputImageType::IndexType localIndex;
  InputImageType::SpacingType spacing;

  typedef  itk::ImageFileReader< InputImageType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputVolume.c_str() );
  try
    {
    reader->Update();
    }
  catch( itk::ExceptionObject & excep )
    {
    std::cerr << "Exception caught !" << std::endl;
    std::cerr << excep << std::endl;
    }
  InputImageType::Pointer localImage = reader->GetOutput();
  spacing = localImage->GetSpacing();
  std::cout << "Computing Hough Map" << std::endl;

  typedef itk::HoughTransformRadialVotingImageFilter< InputImageType,
               InternalImageType > HoughTransformFilterType;
  HoughTransformFilterType::Pointer houghFilter = HoughTransformFilterType::New();
  houghFilter->SetInput( reader->GetOutput() );
  houghFilter->SetNumberOfSpheres( numberOfSpheres );
  houghFilter->SetMinimumRadius(   minRadius );
  houghFilter->SetMaximumRadius(   maxRadius );
  houghFilter->SetSigmaGradient( sigmaGradient );
  houghFilter->SetVariance( variance );
  houghFilter->SetSphereRadiusRatio( sphereRadiusRatio );
  houghFilter->SetVotingRadiusRatio( votingRadiusRatio );
  houghFilter->SetThreshold( threshold );
  houghFilter->SetOutputThreshold( outputThreshold );
  houghFilter->SetGradientThreshold( gradientThreshold );
  houghFilter->SetNbOfThreads( nbOfThreads );
  houghFilter->SetSamplingRatio( samplingRatio );
  houghFilter->Update();

  InternalImageType::Pointer localAccumulator = houghFilter->GetOutput();
  
  
  
  
  
  
  
  
  HoughTransformFilterType::SpheresListType circles;
  circles = houghFilter->GetSpheres( );
  
  // Computing the circles output
  OutputImageType::Pointer  localOutputImage = OutputImageType::New();

  OutputImageType::RegionType region; 
  region.SetSize( localImage->GetLargestPossibleRegion().GetSize() );
  region.SetIndex( localImage->GetLargestPossibleRegion().GetIndex() );
  localOutputImage->SetRegions( region );
  localOutputImage->SetOrigin(localImage->GetOrigin());
  localOutputImage->SetSpacing(localImage->GetSpacing());
  localOutputImage->Allocate();
  localOutputImage->FillBuffer(0);

  typedef HoughTransformFilterType::SpheresListType SpheresListType;
  SpheresListType::const_iterator itSpheres = circles.begin();
  
  
  // std::stringstream position;
  std::ofstream myfile;
  myfile.open("./output.txt");
  std::stringstream out;
  unsigned int count = 1;
  while( itSpheres != circles.end() )
  // while( count != 5 )
    {
    
    
    // out << "Found " << circles.size() << " circle(s)." << std::endl;
    // out << "Center: ";
    out << (*itSpheres)->GetObjectToParentTransform()->GetOffset()
              << std::endl;
    // out << "Radius: " << (*itSpheres)->GetRadius()[0] << std::endl;
    // out << "\n";
    
    // for(double angle = 0;angle <= 2*vnl_math::pi; angle += vnl_math::pi/60.0 )
    //   {
    //   localIndex[0] =
    //      (long int)((*itSpheres)->GetObjectToParentTransform()->GetOffset()[0]
    //          + ( (*itSpheres)->GetRadius()[0]*vcl_cos(angle) )/spacing[0] );
    //   localIndex[1] =
    //      (long int)((*itSpheres)->GetObjectToParentTransform()->GetOffset()[1]
    //          + ( (*itSpheres)->GetRadius()[1]*vcl_sin(angle) )/spacing[1] );
    //   OutputImageType::RegionType outputRegion =
    //                               localOutputImage->GetLargestPossibleRegion();

    //   if( outputRegion.IsInside( localIndex ) )
    //     {
    //     localOutputImage->SetPixel( localIndex, count );
    //     }
    //   }
    itSpheres++;
    count++;
    }
  
    std::string s;
    s = out.str();
    myfile << s;
    
    myfile.close();
  
  
  typedef  itk::ImageFileWriter< InternalImageType  > InputWriterType;
  InputWriterType::Pointer writer = InputWriterType::New();

  writer->SetFileName( outputVolume.c_str() );
  writer->SetInput( localAccumulator );
  writer->SetUseCompression( true );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & excep )
    {
    std::cerr << "Exception caught !" << std::endl;
    std::cerr << excep << std::endl;
    }

  return EXIT_SUCCESS;
}