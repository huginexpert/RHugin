\name{set.logfile}
\alias{set.logfile}

\title{Set Log File}

\description{Set a log file for a Hugin domain.}

\usage{
set.logfile(domain, filename)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{filename}{a character string specifying the name of the log file.}
}

\details{
Certain Hugin operations (compilation, triangulation, table generation, learning and sometimes propagation) can log thier progress in a text file. Setting a log file enables this feature. Calling \code{set.logfile} with \code{filename = NULL} stops logging and closes the logfile connection.
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_domain_set_log_file}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
# Create an RHugin domain
hd <- hugin.domain()

# Set the log file
set.logfile(hd, "hd.log")

# Compile, triangulate, etc.

# Close log file
set.logfile(hd, NULL)
}

\keyword{programming}


