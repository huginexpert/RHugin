\name{errors}
\alias{RHugin.handle.error}
\alias{error.code}
\alias{error.description}

\title{Handling Hugin Errors}

\description{
\code{error.code} returns the error code (or status) set by the most recent Hugin API call.  For a given error code, \code{error.description} returns the name and a brief description of the error that occurred.  \code{RHugin.handle.error} checks whether the most recent Hugin API call produced an error and, if so, prints a brief description of the error and halts the current execution.
}

\usage{
error.code()
error.description(code)
RHugin.handle.error(status)
}

\arguments{
  \item{code}{an integer value specifying a Hugin error code (usually obtained by calling \code{error.code()}).}
  \item{status}{an integer value specifying a Hugin error code.}
}

\details{
An error code of \code{0} indicates that the most recent Hugin API call was successfully executed.
}

\value{
  \item{error.code}{an integer value containing the Hugin error code.}

  \item{error.description}{a list with two elements containing respectively the name and description of the error that occured.}

  \item{RHugin.handle.error}{a \code{NULL} value is invisibly returned.}
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_error_code}, \code{h_error_name} and \code{h_error_description}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
error.description(error.code())
}

\keyword{error}


